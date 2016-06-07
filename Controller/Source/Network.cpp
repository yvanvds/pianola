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

Network::Network(MonitorWindow * monitorWindow)
  : oscReceiver(new OSCReceiver)
  , udpSocket(new DatagramSocket)
  , monitorWindow(monitorWindow)
  , connected(false)
{
  
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

  // empty hashMap
  for (HashMap<String, Robot*>::Iterator i(robots); i.next();) {
    delete i.getValue();
  }
  robots.clear();

  udpSocket->shutdown();
  oscReceiver->disconnect();
}

void Network::oscMessageReceived(const OSCMessage & message) {
  // only interested if message starts with project name
  String address = message.getAddressPattern().toString();
  if (!address.startsWithIgnoreCase(PROJECT)) {
    return;
  }

  // drop project part from address
  // TODO: implement faster algorithm
  address = address.fromFirstOccurrenceOf(PROJECT, false, true);
  String robot = address.fromFirstOccurrenceOf("/", false, true);
  robot = robot.upToFirstOccurrenceOf("/", false, true);

  // find robot with this ID
  if (robots.contains(robot)) {
    robots[robot]->handleMessage(message);
  }
  else {
    monitorWindow->getLog()->addMessage(
      "Unhandled message for " + message.getAddressPattern().toString()
    );
  }

  
}

void Network::oscBundleReceived(const OSCBundle & bundle) {
  monitorWindow->getLog()->addMessage(bundle);
}

void Network::connect() {
  if (oscReceiver->connect(OSC_PORT)) {
    monitorWindow->getLog()->addMessage(String("OSC listening on port ") + String(OSC_PORT));
    connected = true;
  }
  else {
    handleConnectError();
  }
}

void Network::disconnect() {
  if (oscReceiver->disconnect()) {
    monitorWindow->getLog()->addMessage(String("OSC disconnected from port ") + String(OSC_PORT));
    connected = false;
  }
  else {
    handleDisconnectError();
  }
}

void Network::handleConnectError() {
  monitorWindow->getLog()->addMessage(
    "Error: OSC could not connect to port "
    + String(OSC_PORT)
    + ". Perhaps another controller instance is running?"
  );
}

void Network::handleDisconnectError() {
  monitorWindow->getLog()->addMessage(
    String("Error: OSC could not disconnect from port ") + String(OSC_PORT)
  );
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

    if (robots.contains(name)) {
      if (robots[name]->getIp().compareIgnoreCase(udpSender) != 0) {
        robots[name]->setIp(udpSender);
        monitorWindow->getLog()->addMessage(
          "Assigned new ip " + udpSender + " to " + name
        );
      }
    }
    else {
      // TODO: not all robots will be meccanoids!
      Meccanoid * m = new Meccanoid;
      m->setName(name).setIp(udpSender);
      robots.set(name, m);
      monitorWindow->getLog()->addMessage(
        "Meccanoid " + name + " detected with address " + udpSender
      );
    }

  }
}