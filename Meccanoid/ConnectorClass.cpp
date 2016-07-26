#include "pch.h"
#include "ConnectorClass.h"

#include "MainPage.xaml.h"

using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Platform;
using namespace Concurrency;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;


namespace Meccanoid {
  ConnectorClass::ConnectorClass() : serverConnection(nullptr)
  {
    multicastSocket = ref new DatagramSocket();
    multicastSocket->MessageReceived += ref new TypedEventHandler<DatagramSocket^, DatagramSocketMessageReceivedEventArgs^>(this, &ConnectorClass::MulticastReceived);
    multicastSocket->Control->MulticastOnly = true;
    multicastSocket->Control->DontFragment = true;

    create_task(multicastSocket->BindServiceNameAsync("3456")).then(
      [=](task<void> bindTask) {

      try {
        bindTask.get();
        multicastSocket->JoinMulticastGroup(ref new HostName("239.255.42.99"));
      }
      catch (Exception^ exception) {
        delete multicastSocket;
        multicastSocket = nullptr;
      }
    });
  }



  void ConnectorClass::MulticastReceived(DatagramSocket^ socket, DatagramSocketMessageReceivedEventArgs^ eventArguments) {
    try {
      unsigned int stringLength = eventArguments->GetDataReader()->UnconsumedBufferLength;
      String^ receivedMessage = eventArguments->GetDataReader()->ReadString(stringLength);

      if (receivedMessage == "identify\0") {
        if (serverConnection == nullptr) {
          serverConnection = ref new ServerConnection(eventArguments->RemoteAddress);
        }
        else {
          serverConnection->SetServer(eventArguments->RemoteAddress);
        }
      }

    }
    catch (Exception^ exception) {
      // TODO
    }
  }


}
