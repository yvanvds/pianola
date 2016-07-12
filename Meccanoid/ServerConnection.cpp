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
  InitializeCriticalSectionEx(&lock, 0, 0);
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
        NotifyAsync("Listening on port " + udpSocket->Information->LocalPort);
        writer = ref new DataWriter(udpSocket->OutputStream);

        // send id
        writer->WriteString("igor");
        writer->StoreAsync();

      }
      catch (Exception^ exception) {
        NotifyAsync("Listening failed with error: " + exception->Message);
      }
      setupInProgress = false;
      
    });
  }
  else {
    if (writer != nullptr) {
      writer->WriteString("igor");
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

void Meccanoid::ServerConnection::NotifyAsync(Platform::String ^ message)
{
  MainPage::Current->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, message]() {
    MainPage::Current->NotifyUser(message);
  }));
}

void Meccanoid::ServerConnection::Parse(DatagramSocketMessageReceivedEventArgs ^ args)
{
  try {
    MESSAGE command = (MESSAGE) args->GetDataReader()->ReadByte();

    switch (command) {
      case MESSAGE::INIT: {
        NotifyAsync("Init message received");
        break;
      }

      case MESSAGE::LIGHT: {
        NotifyAsync("Light message received");
        break;
      }

      case MESSAGE::SERVO: {
        NotifyAsync("Servo message received");
        break;
      }
    }
  }
  catch (Exception ^ exception) {
    NotifyAsync("Message parsing failed with error: " + exception->Message);
  }
}


