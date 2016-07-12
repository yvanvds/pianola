#pragma once
#include "ServerConnection.h"

using namespace Windows::Networking::Sockets;

namespace Meccanoid {
  ref class ConnectorClass sealed
  {
  public:
    ConnectorClass();

    void SendMessage(Platform::String^ message);

  private:
    DatagramSocket^ multicastSocket;
    ServerConnection^ serverConnection;
    void MulticastReceived(DatagramSocket^ socket, DatagramSocketMessageReceivedEventArgs^ eventArguments);
    void NotifyAsync(Platform::String ^ message);

  };

}

