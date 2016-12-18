#pragma once
#include "AdaHat.h"
#include "Speak.h"

using namespace Windows::Networking;
using namespace Windows::Networking::Sockets;
using namespace Windows::Storage::Streams;
using namespace Platform;
using namespace Windows::Security::ExchangeActiveSyncProvisioning;

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
    void SetNameAsync(String ^ message);
    void SetIPAsync(String ^ ip, String ^ port);
    void Parse        (DatagramSocketMessageReceivedEventArgs ^ args);

    CRITICAL_SECTION lock;

    DatagramSocket^ udpSocket    ;
    HostName      ^ serverAddress;
    DataWriter    ^ writer       ;

    AdaHat ^ hat;
    Speak ^ speaker;

    EasClientDeviceInformation^ info;
    
    bool setupInProgress;
  };
}

