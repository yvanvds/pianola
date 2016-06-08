/*
  ==============================================================================

    Network.cpp
    Created: 4 Jun 2016 6:26:24pm
    Author:  yvan

  ==============================================================================
*/

#include "Network.h"
#include "MonitorWindow.h"
#include "Defines.h"
#include "Utilities.h"

Network::Network(MonitorWindow * monitorWindow)
  : oscReceiver(new OSCReceiver)
  , udpSocket(new DatagramSocket)
  , monitorWindow(monitorWindow)
  , connected(false)
{
  
  // setup pointer structure for robots
  for (int i = 0; i < I_NUM; i++) robots[i] = nullptr;

  // setup osc
  oscReceiver->addListener(this);
  oscReceiver->registerFormatErrorHandler(
    [this] (const char * data, int dataSize) 
    {
      this->monitorWindow->getLog()->addInvalidPacket(data, dataSize);
    }
  );

  // setup udp (for discovering robots on network)
  udpSocket->bindToPort(UDP_PORT);
  startTimer(1000);
}

Network::~Network() {
  stopTimer();

  // empty robot array
  for (int i = 0; i < I_NUM; i++) {
    delete robots[i];
  }

  udpSocket->shutdown();
  oscReceiver->disconnect();
}

void Network::oscMessageReceived(const OSCMessage & message) {
  // tokenize addressPattern
  Array<String> tokens;
  OSCTokenize(tokens, message.getAddressPattern().toString());

  // all AddressPatterns should at least be 3 parts, first is project name
  if (tokens.size() < 3) goto unhandled; // important!!! (robot handleMessage depends on this check)
  if (tokens[0] != PROJECT) goto unhandled;

  // second tokens should be identity
  IDENTITY i = toIdentity(tokens[1]);
  if (!isValid(i)) goto unhandled;

  // if robot is online, let it take care of the message
  if (robots[i] != nullptr) {
    robots[i]->handleMessage(tokens, message);
  }
  else {
    ToLog("Message for offline robot: ");
    ToLog(message);
  }
  return;

unhandled:
  ToLog("Unhandled message:");
  ToLog(message);
  
}

void Network::oscBundleReceived(const OSCBundle & bundle) {
  monitorWindow->getLog()->addMessage(bundle);
}

void Network::connect() {
  if (oscReceiver->connect(OSC_PORT)) {
    ToLog(String("OSC listening on port ") + String(OSC_PORT));
    connected = true;
  }
  else {
    handleConnectError();
  }
}

void Network::disconnect() {
  if (oscReceiver->disconnect()) {
    ToLog(String("OSC disconnected from port ") + String(OSC_PORT));
    connected = false;
  }
  else {
    handleDisconnectError();
  }
}

void Network::handleConnectError() {
  ToLog(
    "Error: OSC could not connect to port "
    + String(OSC_PORT)
    + ". Perhaps another controller instance is running?"
  );
}

void Network::handleDisconnectError() {
  ToLog(String("Error: OSC could not disconnect from port ") + String(OSC_PORT));
}

bool Network::isConnected() {
  return connected;
}

void Network::timerCallback() {
  int bytesRead = udpSocket->read(&udpBuffer, 1024, false, udpSender, udpPort);
  if (bytesRead > 0) {
    String name;
    for (int i = 0; i < bytesRead; i++) {
      name += udpBuffer[i];
    }

    IDENTITY i = toIdentity(name);
    if (isValid(i)) {
      // TODO change condition when other robots are decided upon
      if (i < I_ALL) {
        if (robots[i] == nullptr) {
          robots[i] = new Meccanoid;
          robots[i]->setIp(udpSender).setName(name);
          ToLog("Meccanoid " + name + " detected with address " + udpSender);
        }
        else {
          if (robots[i]->getIp().compareIgnoreCase(udpSender) != 0) {
            robots[i]->setIp(udpSender);
            ToLog("Assigned new ip " + udpSender + " to " + name);
          }
        }
        
      }
    }


  }
}