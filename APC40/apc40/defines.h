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