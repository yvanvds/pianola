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
#include "Meccanoid.h"




class MonitorWindow;

class Network : private OSCReceiver::Listener<OSCReceiver::RealtimeCallback>
              , private Timer {
public:
  Network(MonitorWindow * monitorWindow);
 ~Network();

  void oscMessageReceived(const OSCMessage & message) override;
  void oscBundleReceived (const OSCBundle  & bundle ) override;

  void requestIdentify();

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
  ScopedPointer<DatagramSocket> udpSendSocket;
  ScopedPointer<DatagramSocket> udpRecvSocket;
  int multicastTimer;
  char   udpBuffer[1024];
  String udpSender;
  int    udpPort  ;

  // for visual feedback
  MonitorWindow * monitorWindow;
};



#endif  // NETWORK_H_INCLUDED
