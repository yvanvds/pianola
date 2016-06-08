/*
  ==============================================================================

    Network.h
    Created: 4 Jun 2016 6:26:24pm
    Author:  yvan

  ==============================================================================
*/

#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include "JuceHeader.h"
#include "Robot.h"
#include "Meccanoid.h"
#include "../../pianola_external/pianola/Enums.h"

const int OSC_PORT = 34567;
const int UDP_PORT = 3456;

class MonitorWindow;

class Network : private OSCReceiver::Listener<OSCReceiver::RealtimeCallback>
              , private Timer {
public:
  Network(MonitorWindow * monitorWindow);
 ~Network();

  void oscMessageReceived(const OSCMessage & message) override;
  void oscBundleReceived (const OSCBundle  & bundle ) override;

  void connect   ();
  void disconnect();

  void handleConnectError   ();
  void handleDisconnectError();
  bool isConnected          ();



private:
  void timerCallback() override;

  // osc socket
  ScopedPointer<OSCReceiver> oscReceiver;
  bool connected;

  // upd socket for client discovery
  ScopedPointer<DatagramSocket> udpSocket;
  char   udpBuffer[1024];
  String udpSender;
  int    udpPort  ;

  // robots
  Robot * robots[I_NUM];

  // for visual feedback
  MonitorWindow * monitorWindow;
};



#endif  // NETWORK_H_INCLUDED
