#pragma once


#define CONCAT_NX(A, B) A ## B
#define CONCAT(A, B) CONCAT_NX(A, B)

#define CLASS CONCAT(ClassName, Class)
#define CLASSMETHOD(name) CONCAT(ClassName, name)

#define CREATESTRUCT(content) typedef struct ClassName { t_object obj; content } ClassName; extern t_class * CLASS
#define CREATECLASSPTR t_class * CLASS
#define DECLARE_T ClassName * T = (ClassName*)object_alloc(CLASS)
#define IMPORT_T ClassName * T

#define SETUP(name, funcNew, funcFree) CLASS = class_new(name, (method)funcNew, (method)funcFree, sizeof(ClassName), 0L, A_GIMME, 0);
#define REGISTER_BOX class_register(CLASS_BOX, CLASS)
#define REGISTER_NOBOX class_register(CLASS_NOBOX, CLASS)

#define PROJECTNAME "/apc40";

enum MIDI_MESSAGE {
  M_NOTEON,
  M_NOTEOFF,
  M_CTRL,
  M_NONE,
};

enum CLIP_LED {
  CL_OFF,
  CL_GREEN,
  CL_GREEN_BLINK,
  CL_RED,
  CL_RED_BLINK,
  CL_ORANGE,
  CL_ORANGE_BLINK,
  CL_INVALID,
};

enum CLIP_MODE {
  CM_OFF,
  CM_SINGLE_ORANGE_GREEN,
  CM_SINGLE_ORANGE_RED,
  CM_TOGGLE_ORANGE_GREEN,
  CM_TOGGLE_ORANGE_RED,
  CM_CUSTOM,
  CM_INVALID,
};

enum SLIDER {
  S_1,
  S_2,
  S_3,
  S_4,
  S_5,
  S_6,
  S_7,
  S_8,
  S_MASTER,
  S_PAN,
  S_INVALID,
};

enum KNOB {
  K_TRACK1,
  K_TRACK2,
  K_TRACK3,
  K_TRACK4,
  K_TRACK5,
  K_TRACK6,
  K_TRACK7,
  K_TRACK8,
  K_DEVICE1,
  K_DEVICE2,
  K_DEVICE3,
  K_DEVICE4,
  K_DEVICE5,
  K_DEVICE6,
  K_DEVICE7,
  K_DEVICE8,
  K_CUE,
  K_INVALID,
};

enum KNOB_STYLE {
  KS_OFF,
  KS_SINGLE,
  KS_VOLUME,
  KS_PAN,
  KS_INVALID,
};

enum BUTTON {
  B_SCENE1,
  B_SCENE2,
  B_SCENE3,
  B_SCENE4,
  B_SCENE5,
  B_STOP1,
  B_STOP2,
  B_STOP3,
  B_STOP4,
  B_STOP5,
  B_STOP6,
  B_STOP7,
  B_STOP8,
  B_STOPALL,
  B_TRACK1,
  B_TRACK2,
  B_TRACK3,
  B_TRACK4,
  B_TRACK5,
  B_TRACK6,
  B_TRACK7,
  B_TRACK8,
  B_TRACKM,
  B_ACT1,
  B_ACT2,
  B_ACT3,
  B_ACT4,
  B_ACT5,
  B_ACT6,
  B_ACT7,
  B_ACT8,
  B_SOLO1,
  B_SOLO2,
  B_SOLO3,
  B_SOLO4,
  B_SOLO5,
  B_SOLO6,
  B_SOLO7,
  B_SOLO8,
  B_REC1,
  B_REC2,
  B_REC3,
  B_REC4,
  B_REC5,
  B_REC6,
  B_REC7,
  B_REC8,
  B_PAN,
  B_SENDA,
  B_SENDB,
  B_SENDC,
  B_SHIFT,
  B_SELECT_UP,
  B_SELECT_DOWN,
  B_SELECT_LEFT,
  B_SELECT_RIGHT,
  B_TAP,
  B_NUDGE_MIN,
  B_NUDGE_PLUS,
  B_CLIP,
  B_DEVICE,
  B_ARROW_LEFT,
  B_ARROW_RIGHT,
  B_DETAIL,
  B_QUANTIZE,
  B_OVERDUB,
  B_METRONOME,
  B_PLAY,
  B_STOP,
  B_REC,
  B_INVALID,
};