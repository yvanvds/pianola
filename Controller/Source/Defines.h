/*
  ==============================================================================

    Defines.h
    Created: 7 Jun 2016 7:43:36pm
    Author:  yvan

  ==============================================================================
*/

#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include "JuceHeader.h"

const String PROJECT = "pianola";
const int OSC_PORT = 34567;
const int MULTICAST_PORT = 3456;
const int MESSAGE_PORT = 3457;
const String MULTICAST = "239.255.42.99";

const unsigned int SERVO_COUNT = 16;

#define PI_6 0.52359878f // PI/6 ( 30 deg)
#define PI_4 0.78539816f // PI/4 ( 45 deg)
#define PI_3 1.04719755f // PI/3 ( 60 deg)
#define PI_2 1.57079633f // PI/2 ( 90 deg)
#define PI   3.14159265f // PI   (180 deg)
#define PI2  6.28318531f // PI*2 (360 deg)

#define PID_6 0.5235987755982988 // PI/6 ( 30 deg) Dbl
#define PID_4 0.7853981633974483 // PI/4 ( 45 deg) Dbl
#define PID_3 1.0471975511965977 // PI/3 ( 60 deg) Dbl
#define PID_2 1.5707963267948966 // PI/2 ( 90 deg) Dbl
#define PID   3.1415926535897932 // PI   (180 deg) Dbl
#define PID2  6.2831853071795864 // PI*2 (360 deg) Dbl

#endif  // DEFINES_H_INCLUDED
