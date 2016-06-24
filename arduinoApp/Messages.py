class Message:
  ANNOUNCE = 0

class Command:
  MeccanoidSetServoMotorPosition = 0
  MeccanoidSetServoLedColor = 1
  MeccanoidSetLedColor = 2
  MeccanoidGetServoMotorPosition = 3
  MeccanoidDisableServoMotor = 4
  StepperMotorStep = 5
  StepperMotorDisable = 6
  AnalogRead = 7
  AnalogWrite = 8
  DigitalRead = 8
  DigitalWrite = 10
  Acknowledge = 11
  AnalogPinMode = 12
  DigitalPinMode = 13
  MeccanoidInitialise = 14
  Version = 15
  Break = 16
