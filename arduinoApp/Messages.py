class Message:
  ANNOUNCE = 0

class MB: # BYTE MESSAGE POSITION
  CHANGE           =  0 # content has changed 
  PIN_ID1          =  1 # ID of first pin (will be initialized if needed)
  ID1_SERVO0_POS   =  2 # desired position of first servo [24 - 232]
  ID1_SERVO0_TIME  =  3 # desired time to reach position in millis / 100 [0 - 255]
  ID1_SERVO0_LIGHT =  4 # light color of this servo [0-7]
  ID1_SERVO1_POS   =  5 # same for other servo's
  ID1_SERVO1_TIME  =  6
  ID1_SERVO1_LIGHT =  7
  ID1_SERVO2_POS   =  8
  ID1_SERVO2_TIME  =  9
  ID1_SERVO2_LIGHT = 10
  PIN_ID2          = 11 # same for other pins
  ID2_SERVO0_POS   = 12
  ID2_SERVO0_TIME  = 13
  ID2_SERVO0_LIGHT = 14
  ID2_SERVO1_POS   = 15
  ID2_SERVO1_TIME  = 16
  ID2_SERVO1_LIGHT = 17
  ID2_SERVO2_POS   = 18
  ID2_SERVO2_TIME  = 19
  ID2_SERVO2_LIGHT = 20
  PIN_ID3          = 21
  ID3_SERVO0_POS   = 22
  ID3_SERVO0_TIME  = 23
  ID3_SERVO0_LIGHT = 24
  ID3_SERVO1_POS   = 25
  ID3_SERVO1_TIME  = 26
  ID3_SERVO1_LIGHT = 27
  ID3_SERVO2_POS   = 28
  ID3_SERVO2_TIME  = 29
  ID3_SERVO2_LIGHT = 30
  LIGHT_R          = 31 # red color byte for head light
  LIGHT_G          = 32 # green
  LIGHT_B          = 33 # blue
  LIGHT_F          = 34 # alpha / intensity
  NUM              = 35 # total number of bytes in a message


