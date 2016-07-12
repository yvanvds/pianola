// 
// 
// 

#include <Bridge.h>
#include "bridgeController.h"
#include "meccanoid.h"


BridgeControllerClass::BridgeControllerClass()
{
  memset(newMessages, 0, MB_NUM);
  memset(oldMessages, 0, MB_NUM);
}

void BridgeControllerClass::start() {
  for(byte i = 0; i < 6; i++) {
    delay(5000);
    Serial.println("Waiting for bridge: " + String(30 - 5*i));
  }
  
  Bridge.begin();
  Bridge.put(MESSAGE, newMessages);
  Serial.println("Bridge Started.");

  // start python script  
  p.begin("/mnt/sda/runScript");
  p.addParameter("&");
  p.runAsynchronously();
  Serial.println("Yun script started.");
}

void BridgeControllerClass::update() {
  int startTime = millis();
  // forward script output to serial monitor
  //while(p.available() > 0) {
  //  Serial.print(p.read());
  //}
  Bridge.get(MESSAGE, newMessages, MB_NUM);
  
  // different value means there is a new message
  if (newMessages[MB_CHANGE] != oldMessages[MB_CHANGE]) {
    
    // print message for debug
    //for(byte i = 0; i < MB_NUM; i++) {
    //  Serial.print(String((unsigned char)newMessages[i]) + ",");
    //}
    //Serial.print(" \n");
    
    // check active pins
    byte pin1 = newMessages[MB_PIN_ID1];
    byte pin2 = newMessages[MB_PIN_ID2];
    byte pin3 = newMessages[MB_PIN_ID3];
    Meccanoid.initIfNeeded(pin1);
    Meccanoid.initIfNeeded(pin2);
    Meccanoid.initIfNeeded(pin3);

    /////////////////////////////////////
    // update servo positions if changed
    /////////////////////////////////////
    
    // first pin:
    if (newMessages[MB_ID1_SERVO0_POS] != oldMessages[MB_ID1_SERVO0_POS]
     || newMessages[MB_ID1_SERVO0_TIME] != oldMessages[MB_ID1_SERVO0_TIME]) {
      Meccanoid.setServoPos(pin1, 0, newMessages[MB_ID1_SERVO0_POS], newMessages[MB_ID1_SERVO0_TIME]);
    }

    if (newMessages[MB_ID1_SERVO1_POS] != oldMessages[MB_ID1_SERVO1_POS]
      || newMessages[MB_ID1_SERVO1_TIME] != oldMessages[MB_ID1_SERVO1_TIME]) {
      Meccanoid.setServoPos(pin1, 1, newMessages[MB_ID1_SERVO1_POS], newMessages[MB_ID1_SERVO1_TIME]);
    }

    if (newMessages[MB_ID1_SERVO2_POS] != oldMessages[MB_ID1_SERVO2_POS]
      || newMessages[MB_ID1_SERVO2_TIME] != oldMessages[MB_ID1_SERVO2_TIME]) {
      Meccanoid.setServoPos(pin1, 2, newMessages[MB_ID1_SERVO2_POS], newMessages[MB_ID1_SERVO2_TIME]);
    }

    // second pin:
    if (newMessages[MB_ID2_SERVO0_POS] != oldMessages[MB_ID2_SERVO0_POS]
      || newMessages[MB_ID2_SERVO0_TIME] != oldMessages[MB_ID2_SERVO0_TIME]) {
      Meccanoid.setServoPos(pin2, 0, newMessages[MB_ID2_SERVO0_POS], newMessages[MB_ID2_SERVO0_TIME]);
    }

    if (newMessages[MB_ID2_SERVO1_POS] != oldMessages[MB_ID2_SERVO1_POS]
      || newMessages[MB_ID2_SERVO1_TIME] != oldMessages[MB_ID2_SERVO1_TIME]) {
      Meccanoid.setServoPos(pin2, 1, newMessages[MB_ID2_SERVO1_POS], newMessages[MB_ID2_SERVO1_TIME]);
    }

    if (newMessages[MB_ID2_SERVO2_POS] != oldMessages[MB_ID2_SERVO2_POS]
      || newMessages[MB_ID2_SERVO2_TIME] != oldMessages[MB_ID2_SERVO2_TIME]) {
      Meccanoid.setServoPos(pin2, 2, newMessages[MB_ID2_SERVO2_POS], newMessages[MB_ID2_SERVO2_TIME]);
    }

    // third pin:
    if (newMessages[MB_ID3_SERVO0_POS] != oldMessages[MB_ID3_SERVO0_POS]
      || newMessages[MB_ID3_SERVO0_TIME] != oldMessages[MB_ID3_SERVO0_TIME]) {
      Meccanoid.setServoPos(pin3, 0, newMessages[MB_ID3_SERVO0_POS], newMessages[MB_ID3_SERVO0_TIME]);
    }

    if (newMessages[MB_ID3_SERVO1_POS] != oldMessages[MB_ID3_SERVO1_POS]
      || newMessages[MB_ID3_SERVO1_TIME] != oldMessages[MB_ID3_SERVO1_TIME]) {
      Meccanoid.setServoPos(pin3, 1, newMessages[MB_ID3_SERVO1_POS], newMessages[MB_ID3_SERVO1_TIME]);
    }

    if (newMessages[MB_ID3_SERVO2_POS] != oldMessages[MB_ID3_SERVO2_POS]
      || newMessages[MB_ID3_SERVO2_TIME] != oldMessages[MB_ID3_SERVO2_TIME]) {
      Meccanoid.setServoPos(pin3, 2, newMessages[MB_ID3_SERVO2_POS], newMessages[MB_ID3_SERVO2_TIME]);
    }

    ////////////////////
    // servo lights
    ////////////////////

    // first pin:
    if (newMessages[MB_ID1_SERVO0_LIGHT] != oldMessages[MB_ID1_SERVO0_LIGHT]) {
      Meccanoid.setServoColor(pin1, 0, newMessages[MB_ID1_SERVO0_LIGHT]);
    }

    if (newMessages[MB_ID1_SERVO1_LIGHT] != oldMessages[MB_ID1_SERVO1_LIGHT]) {
      Meccanoid.setServoColor(pin1, 1, newMessages[MB_ID1_SERVO1_LIGHT]);
    }

    if (newMessages[MB_ID1_SERVO2_LIGHT] != oldMessages[MB_ID1_SERVO2_LIGHT]) {
      Meccanoid.setServoColor(pin1, 2, newMessages[MB_ID1_SERVO2_LIGHT]);
    }

    // second pin:
    if (newMessages[MB_ID2_SERVO0_LIGHT] != oldMessages[MB_ID2_SERVO0_LIGHT]) {
      Meccanoid.setServoColor(pin2, 0, newMessages[MB_ID2_SERVO0_LIGHT]);
    }

    if (newMessages[MB_ID2_SERVO1_LIGHT] != oldMessages[MB_ID2_SERVO1_LIGHT]) {
      Meccanoid.setServoColor(pin2, 1, newMessages[MB_ID2_SERVO1_LIGHT]);
    }

    if (newMessages[MB_ID2_SERVO2_LIGHT] != oldMessages[MB_ID2_SERVO2_LIGHT]) {
      Meccanoid.setServoColor(pin2, 2, newMessages[MB_ID2_SERVO2_LIGHT]);
    }

    // third pin:
    if (newMessages[MB_ID3_SERVO0_LIGHT] != oldMessages[MB_ID3_SERVO0_LIGHT]) {
      Meccanoid.setServoColor(pin3, 0, newMessages[MB_ID3_SERVO0_LIGHT]);
    }

    if (newMessages[MB_ID3_SERVO1_LIGHT] != oldMessages[MB_ID3_SERVO1_LIGHT]) {
      Meccanoid.setServoColor(pin3, 1, newMessages[MB_ID3_SERVO1_LIGHT]);
    }

    if (newMessages[MB_ID3_SERVO2_LIGHT] != oldMessages[MB_ID3_SERVO2_LIGHT]) {
      Meccanoid.setServoColor(pin3, 2, newMessages[MB_ID3_SERVO2_LIGHT]);
    }

    /////////////////////
    // head light
    /////////////////////
    /*if ( newMessages[MB_LIGHT_R] != oldMessages[MB_LIGHT_R]
      || newMessages[MB_LIGHT_G] != oldMessages[MB_LIGHT_G]
      || newMessages[MB_LIGHT_B] != oldMessages[MB_LIGHT_B]
      || newMessages[MB_LIGHT_F] != oldMessages[MB_LIGHT_F]
      ) {
      Meccanoid.setHeadColor(newMessages[MB_LIGHT_R], newMessages[MB_LIGHT_G], newMessages[MB_LIGHT_B], newMessages[MB_LIGHT_F]);
    }*/

    strcpy(oldMessages, newMessages);
    int duration = millis() - startTime;
    Serial.println("time for update: " + String(duration));
  }
}



BridgeControllerClass BridgeController;

