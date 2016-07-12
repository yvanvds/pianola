/*
  ==============================================================================

    Robot.h
    Created: 7 Jun 2016 7:11:19pm
    Author:  yvan

  ==============================================================================
*/

#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "JuceHeader.h"

class Robot : OSCSender {
public:
  Robot();

  
  String getName(); Robot & setName(const String & value);
  String getIp  (); Robot & setIp  (const String & value);
  
  Robot & resetLastSeen();
  int getLastSeen() { return lastSeen; }
  Robot & update();
  bool isConnected() { return connected; }
  
  void assignSocket(DatagramSocket * socket);
  bool send(const OSCMessage & message);
  bool send(const void * sourceBuffer, int buffersize); // sends over udp socket

  virtual void handleMessage(const Array<String> & tokens, const OSCMessage & message) = 0;

protected:
  String name;
  String ipAddress;
  bool connected;
  int lastSeen;
  DatagramSocket * socket;
};



#endif  // ROBOT_H_INCLUDED
