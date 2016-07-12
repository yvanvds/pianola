#pragma once
using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Platform;

namespace Meccanoid {
  ref class ServerConnection sealed
  {
  public:
    ServerConnection(HostName^ serverAddress);

    void SetServer(HostName^ serverAddress);
    void OnMessage(DatagramSocket ^ udpSocket, DatagramSocketMessageReceivedEventArgs ^ eventArguments);

    DataWriter^ GetWriter();

  private:
    ~ServerConnection();

    void SetupIfNeeded();
    void NotifyAsync  (String ^ message);
    void Parse        (DatagramSocketMessageReceivedEventArgs ^ args);

    CRITICAL_SECTION lock;

    DatagramSocket^ udpSocket    ;
    HostName      ^ serverAddress;
    DataWriter    ^ writer       ;
    
    bool setupInProgress;
  };
}

