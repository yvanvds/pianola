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
#include "Vector.h"
#include "../../Shared/Messages.h"
#include "Fifo.h"

class Robot : OSCSender {
public:
  Robot();

  
  String getName(); Robot & setName(const String & value);
  String getIp  (); Robot & setIp  (const String & value);
  int    getPort(); Robot & setPort(      int      value);
  int    getBufferSize() { return bufferSize; }
  
  Robot & resetLastSeen();
  int getLastSeen() { return lastSeen; }
  virtual void update();
  bool isConnected() { return connected; }
  
  void assignSocket(DatagramSocket * socket);
  bool send(const OSCMessage & message);
  bool send(const void * sourceBuffer, int buffersize); // sends over udp socket

  virtual void handleMessage(const OSCMessage & message) = 0;

  void ConvertVecToRotation(Vec & coord, BODYPART part);

  void timerCallback();

protected:
  

  ReadWriteLock lock;

  String name;
  String ipAddress;
  Atomic<int> port;
  bool connected;
  bool VecToRot;
  int lastSeen;
  int bufferSize;
  DatagramSocket * socket;

  Fifo messageBuffer;
};



#endif  // ROBOT_H_INCLUDED
