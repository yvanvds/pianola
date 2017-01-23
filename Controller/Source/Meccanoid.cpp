/*
  ==============================================================================

    Meccanoid.cpp
    Created: 7 Jun 2016 7:11:29pm
    Author:  yvan

  ==============================================================================
*/

#include "Meccanoid.h"
#include "JuceHeader.h"
#include "Defines.h"
#include "MonitorWindow.h"
#include "Poses.h"
#include "../../Shared/Messages.h"
#include "KinectPlayer.h"


Meccanoid::Meccanoid() {
  for (unsigned int i = 0; i < (unsigned int)BODYPART::INVALID; i++) {
    part[i].init((BODYPART)i);
  }
}

void Meccanoid::handleMessage(const OSCMessage & message) {
  // we already have tested there are 3 tokens or more
  
	if (message[1].getString().equalsIgnoreCase("rotate")) {
    if (message.size() != 7) {
      ToLog("Invalid bone rotation");
    }
    else {
      BodyPart & part = getBodyPart(message[2].getString());
      if (!part.valid()) {
        ToLog("Invalid body part: " + message[2].getString());
      } else {
        MemoryOutputStream out;
        part.writeOrn(out, message);
        send(out.getData(), out.getDataSize());
      }
    }
    return; // message is handled
  }

  if (message[1].getString().equalsIgnoreCase("relrotate")) {
    if (message.size() != 7) {
      ToLog("Invalid relative bone rotation");
    }
    else {
      BodyPart & part = getBodyPart(message[2].getString());
      if (!part.valid()) {
        ToLog("Invalid body part: " + message[2].getString());
      }
      else {
        MemoryOutputStream out;
        part.writeRelOrn(out, message);
        send(out.getData(), out.getDataSize());
      }
    }
    return; // message is handled
  }

  if (message[1].getString().equalsIgnoreCase("kinect")) {
    if (message.size() != 4) {
      ToLog("Invalid kinect message");
    }
    else {
      String recording = message[2].getString();
      float speed = message[3].getFloat32();
      Player().play(recording, speed, name);
    }
    return;
  }

  if (message[1].getString().equalsIgnoreCase("constraint")) {
    if (message.size() != 4) {
      ToLog("Invalid bone constraint");
    }
    else {
      BodyPart & part = getBodyPart(message[2].getString());
      if (!part.valid()) {
        ToLog("Invalid body part: " + message[2].getString());
      }
      else {
        MemoryOutputStream out;
        part.writeConstraint(out, message);
        send(out.getData(), out.getDataSize());
      }
    }
    return; // message is handled
  }

  if (message[1].getString().equalsIgnoreCase("brown")) {
    if (message.size() != 5) {
      ToLog("Invalid brown message");
    }
    else {
      BodyPart & part = getBodyPart(message[2].getString());
      if (!part.valid()) {
        ToLog("Invalid body part: " + message[2].getString());
      }
      else {
        MemoryOutputStream out;
        part.writeBrown(out, message);
        send(out.getData(), out.getDataSize());
      }
    }
    return; // message is handled
  }

  if (message[1].getString().equalsIgnoreCase("textMessage")) {
    if (message.size() != 4) {
      ToLog("Invalid Text Message");
    }
    else {
      MemoryOutputStream out;
      out.writeByte((unsigned char)MESSAGE::SPEAK);

      // write foreground ID and alpha
      String msg = message[2].getString();
      const char * bytes = msg.getCharPointer();
      int size = msg.getNumBytesAsUTF8();
      out.writeIntBigEndian(size);
      for (int i = 0; i < size; i++) {
        out.writeByte(bytes[i]);
      }

      // send it
      send(out.getData(), out.getDataSize());
    }
    return;
  }

  // if we get here, the message was not handled
  ToLog("Invalid message: ");
  ToLog(message);

}



void Meccanoid::initialize() {
  unsigned char out[1];
  out[0] = (unsigned char) MESSAGE::INIT;
  send(&out, 1);

  for (int i = 0; i < (int)BODYPART::INVALID; i++) {
    {
      MemoryOutputStream out;
      part[i].writeConstraints(out);
      send(out.getData(), out.getDataSize());
    }
    {
      MemoryOutputStream out;
      part[i].writeLimits(out);
      send(out.getData(), out.getDataSize());
    }
    
  }

}

Servo * Meccanoid::getServo(const String & name)
{
  for (int i = 0; i < SERVO_COUNT; i++) {
    if (servo[i].getName().equalsIgnoreCase(name)) {
      return &servo[i];
    }
  }
  return nullptr;
}

Servo * Meccanoid::getServo(unsigned int ID)
{
  if (ID < SERVO_COUNT) {
    return &servo[ID];
  }
  return nullptr;
}

void Meccanoid::resetServos()
{
  for (int i = 0; i < SERVO_COUNT; i++) {
    servo[i].reset();
  }
}

BodyPart & Meccanoid::getBodyPart(BODYPART part)
{
   return this->part[(unsigned int)part];
}

BodyPart & Meccanoid::getBodyPart(const String & name) {
  BODYPART part;
  if (name.equalsIgnoreCase("head"         )) part = BODYPART::HEAD;
  else if (name.equalsIgnoreCase("armLeftUpper" )) part = BODYPART::ARMLU;
  else if (name.equalsIgnoreCase("armLeftLower" )) part = BODYPART::ARMLL;
  else if (name.equalsIgnoreCase("handLeft"     )) part = BODYPART::HANDL;
  else if (name.equalsIgnoreCase("armRightUpper")) part = BODYPART::ARMRU;
  else if (name.equalsIgnoreCase("armRightLower")) part = BODYPART::ARMRL;
  else if (name.equalsIgnoreCase("handRight"    )) part = BODYPART::HANDR;
  else if (name.equalsIgnoreCase("legLeftUpper" )) part = BODYPART::LEGLU;
  else if (name.equalsIgnoreCase("legLeftLower" )) part = BODYPART::LEGLL;
  else if (name.equalsIgnoreCase("legRightUpper")) part = BODYPART::LEGRU;
  else if (name.equalsIgnoreCase("legRightLower")) part = BODYPART::LEGRL;
  else part = BODYPART::INVALID;

  return getBodyPart(part);
}

