#include "pch.h"
#include "ServerConnection.h"
#include "MainPage.xaml.h"
#include "../Shared/Messages.h"

using namespace Platform;
using namespace Concurrency;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Connectivity;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Core;

Meccanoid::ServerConnection::ServerConnection(HostName^ serverAddress)
{
  this->udpSocket = nullptr;
  this->writer    = nullptr;
  
  // for device name
  info = ref new EasClientDeviceInformation;
  
  InitializeCriticalSectionEx(&lock, 0, 0);
  hat = ref new AdaHat();
  hat->init();

  speaker = ref new Speak();

  SetServer(serverAddress);
}

void Meccanoid::ServerConnection::SetServer(HostName ^ serverAddress)
{
  if (!setupInProgress) {
    setupInProgress = true;
    this->serverAddress = serverAddress;
    SetupIfNeeded();
  }
}

void Meccanoid::ServerConnection::OnMessage(DatagramSocket ^ socket, DatagramSocketMessageReceivedEventArgs ^ eventArguments)
{
  Parse(eventArguments);
}

DataWriter ^ Meccanoid::ServerConnection::GetWriter()
{
  if (writer == nullptr) {
    writer = ref new DataWriter(udpSocket->OutputStream);
  }
  return writer;
}

void Meccanoid::ServerConnection::SetupIfNeeded()
{
  if (udpSocket != nullptr) {
    if (udpSocket->Information->RemoteAddress->Equals(serverAddress)) {
      EnterCriticalSection(&lock);
      delete udpSocket;
      udpSocket = nullptr;

      if (writer != nullptr) {
        delete writer;
        writer = nullptr;
      }
      LeaveCriticalSection(&lock);
    }
  }

  if (udpSocket == nullptr) {
    udpSocket = ref new DatagramSocket();
    udpSocket->Control->InboundBufferSizeInBytes = 32;
    udpSocket->MessageReceived += ref new TypedEventHandler<DatagramSocket^, DatagramSocketMessageReceivedEventArgs^>(this, &ServerConnection::OnMessage);
    udpSocket->Control->DontFragment = true;

    // bind to local port
    udpSocket->BindServiceNameAsync("3457");

    // bind to remote server
    create_task(udpSocket->ConnectAsync(serverAddress, "3457")).then([this](task<void> previousTask) {
      try {
        previousTask.get();

        writer = ref new DataWriter(udpSocket->OutputStream);

        // send id
        writer->WriteString(info->FriendlyName);
        writer->StoreAsync();

        SetNameAsync(info->FriendlyName);
        SetIPAsync(udpSocket->Information->LocalAddress->ToString(), udpSocket->Information->LocalPort);
      }
      catch (Exception^ exception) {

      }
      setupInProgress = false;
      
    });
  }
  else {
    if (writer != nullptr) {
      writer->WriteString(info->FriendlyName);
      writer->StoreAsync();
    }
    setupInProgress = false;
  }
}

Meccanoid::ServerConnection::~ServerConnection()
{
  delete udpSocket;
  udpSocket = nullptr;

  if (writer != nullptr) {
    delete writer;
    writer = nullptr;
  }

  DeleteCriticalSection(&lock);
}

void Meccanoid::ServerConnection::SetNameAsync(Platform::String ^ message)
{
  MainPage::Current->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, message]() {
    MainPage::Current->SetName(message);
  }));
}

void Meccanoid::ServerConnection::SetIPAsync(String ^ ip, String ^ port)
{
  MainPage::Current->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, ip, port]() {
    MainPage::Current->SetIP(ip, port);
  }));
}



void Meccanoid::ServerConnection::Parse(DatagramSocketMessageReceivedEventArgs ^ args)
{
  try {
    MESSAGE command = (MESSAGE) args->GetDataReader()->ReadByte();

    switch (command) {
      case MESSAGE::INIT: {
        hat->reset();
        break;
      }

      case MESSAGE::SYSTEM: {
        byte message = args->GetDataReader()->ReadByte();
        if (message == 0) {

        }
        break;
      }

      case MESSAGE::BROWN: {
        BODYPART part = (BODYPART)args->GetDataReader()->ReadByte();
        byte factor = args->GetDataReader()->ReadByte();
        float speed = args->GetDataReader()->ReadSingle();
        hat->setBrown(part, factor, speed);
        break;
      }

      case MESSAGE::JOINTROTATE: {
        BODYPART part = (BODYPART)args->GetDataReader()->ReadByte();       
        byte x = args->GetDataReader()->ReadByte();
        byte y = args->GetDataReader()->ReadByte();
        float speed = args->GetDataReader()->ReadSingle();
        hat->setRotate(part, x, y, speed);
        break;
      }

      case MESSAGE::JOINTRELROTATE: {
        BODYPART part = (BODYPART)args->GetDataReader()->ReadByte();
        byte x = args->GetDataReader()->ReadByte();
        byte y = args->GetDataReader()->ReadByte();
        float speed = args->GetDataReader()->ReadSingle();
        hat->setRelRotate(part, x, y, speed);
        break;
      }

      case MESSAGE::JOINTOFFSET: {
        // warning: in this context, the offset is a rotation offset
        int test = args->GetDataReader()->ReadByte();
        //if (test == 6) {
          BODYPART part = (BODYPART)test;
          int x = args->GetDataReader()->ReadInt32();
          int y = args->GetDataReader()->ReadInt32();
          hat->setOffset(part, x, y);
        //}
        
        break;
      }

      case MESSAGE::CONSTRAIN: {
        BODYPART part = (BODYPART)args->GetDataReader()->ReadByte();
        float value = args->GetDataReader()->ReadSingle();
        hat->setConstraintMultiplier(part, value);
        break;
      }

      case MESSAGE::SETCONSTRAINTS: {
        BODYPART part = (BODYPART)args->GetDataReader()->ReadByte();
        byte minX = args->GetDataReader()->ReadByte();
        byte maxX = args->GetDataReader()->ReadByte();
        byte minY = args->GetDataReader()->ReadByte();
        byte maxY = args->GetDataReader()->ReadByte();
        hat->setConstraints(part, minX, minY, maxX, maxY);
        break;
      }

      case MESSAGE::SETLIMITS: {
        BODYPART part = (BODYPART)args->GetDataReader()->ReadByte();
        byte minX = args->GetDataReader()->ReadByte();
        byte maxX = args->GetDataReader()->ReadByte();
        byte minY = args->GetDataReader()->ReadByte();
        byte maxY = args->GetDataReader()->ReadByte();
        hat->setLimits(part, minX, minY, maxX, maxY);
        break;
      }

      case MESSAGE::SPEAK: {
        //speaker->start("Hello world.");
        int size = args->GetDataReader()->ReadInt32();
        Platform::String ^ text = args->GetDataReader()->ReadString(size);
        std::wstring wstr(text->Data());
        wstr.erase(0, 5);
        std::replace(wstr.begin(), wstr.end(), '_', ' ');
        std::replace(wstr.begin(), wstr.end(), '$', ',');
        Platform::String ^ result = ref new Platform::String(wstr.c_str());
        speaker->start(result);
        break;
      }
    }
  }
  catch (Exception ^ exception) {

  }
}


