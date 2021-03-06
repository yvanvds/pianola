#include "apc40.h"
#include "Button.h"
#include <String>
#include "ButtonManager.h"

CREATECLASSPTR;

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv) {
  DECLARE_T;

  T->ID = B_INVALID;
  T->active = true;

  if (argc < 1) {
    object_post((t_object *)T, "I need a knob name as first argument");
    return T;
  }

  if ((argv)->a_type == A_SYM) {
    std::string s; s = atom_getsym(argv)->s_name;
    if (s == "scene") {
      if (argc < 2) {
        object_post((t_object *)T, "I need a number for a scene button");
        return T;
      }
      else {
        int v = (int)atom_getlong(argv + 1);
        switch (v) {
        case 1: T->ID = B_SCENE1; break;
        case 2: T->ID = B_SCENE2; break;
        case 3: T->ID = B_SCENE3; break;
        case 4: T->ID = B_SCENE4; break;
        case 5: T->ID = B_SCENE5; break;
        default: T->ID = B_INVALID; break;
        }
      }
    }
    else if (s == "stop") {
      if (argc == 2) {
        std::string s; s = atom_getsym(argv + 1)->s_name;
        if (s == "all") {
          T->ID = B_STOPALL;
        }
        else T->ID = B_INVALID;
      }
      else {
        T->ID = B_STOP;
      }
    }
    else if (s == "track") {
      if (argc < 2) {
        object_post((t_object *)T, "I need a number for a track button");
        return T;
      }
      else {
        if ((argv + 1)->a_type == A_SYM) {
          std::string s; s = atom_getsym(argv + 1)->s_name;
          if (s == "master") {
            T->ID = B_TRACKM;
          }
          else T->ID = B_INVALID;
        }
        else {
          int v = (int)atom_getlong(argv + 1);
          switch (v) {
          case 1: T->ID = B_TRACK1; break;
          case 2: T->ID = B_TRACK2; break;
          case 3: T->ID = B_TRACK3; break;
          case 4: T->ID = B_TRACK4; break;
          case 5: T->ID = B_TRACK5; break;
          case 6: T->ID = B_TRACK6; break;
          case 7: T->ID = B_TRACK7; break;
          case 8: T->ID = B_TRACK8; break;
          default: T->ID = B_INVALID; break;
          }
        }
      }
    }
    else if (s == "activator") {
      if (argc < 2) {
        object_post((t_object *)T, "I need a number for an activator button");
        return T;
      }
      else {
        int v = (int)atom_getlong(argv + 1);
        switch (v) {
        case 1: T->ID = B_ACT1; break;
        case 2: T->ID = B_ACT2; break;
        case 3: T->ID = B_ACT3; break;
        case 4: T->ID = B_ACT4; break;
        case 5: T->ID = B_ACT5; break;
        case 6: T->ID = B_ACT6; break;
        case 7: T->ID = B_ACT7; break;
        case 8: T->ID = B_ACT8; break;
        default: T->ID = B_INVALID; break;
        }
      }
    }
    else if (s == "solo") {
      if (argc < 2) {
        object_post((t_object *)T, "I need a number for a solo button");
        return T;
      }
      else {
        int v = (int)atom_getlong(argv + 1);
        switch (v) {
        case 1: T->ID = B_SOLO1; break;
        case 2: T->ID = B_SOLO2; break;
        case 3: T->ID = B_SOLO3; break;
        case 4: T->ID = B_SOLO4; break;
        case 5: T->ID = B_SOLO5; break;
        case 6: T->ID = B_SOLO6; break;
        case 7: T->ID = B_SOLO7; break;
        case 8: T->ID = B_SOLO8; break;
        default: T->ID = B_INVALID; break;
        }
      }
    }
    else if (s == "record") {
      if (argc < 2) {
        T->ID = B_REC;
      }
      else {
        int v = (int)atom_getlong(argv + 1);
        switch (v) {
        case 1: T->ID = B_REC1; break;
        case 2: T->ID = B_REC2; break;
        case 3: T->ID = B_REC3; break;
        case 4: T->ID = B_REC4; break;
        case 5: T->ID = B_REC5; break;
        case 6: T->ID = B_REC6; break;
        case 7: T->ID = B_REC7; break;
        case 8: T->ID = B_REC8; break;
        default: T->ID = B_INVALID; break;
        }
      }
    }
    else if (s == "pan") {
      T->ID = B_PAN;
    }
    else if (s == "send") {
      if (argc < 2) {
        object_post((t_object *)T, "please add a, b, or c");
        return T;
      }
      else {
        std::string s; s = atom_getsym(argv + 1)->s_name;
        if (s == "a") {
          T->ID = B_SENDA;
        }
        else if (s == "b") {
          T->ID = B_SENDB;
        }
        else if (s == "c") {
          T->ID = B_SENDC;
        }
        else {
          T->ID = B_INVALID;
        }
      }
    }
    else if (s == "shift") {
      T->ID = B_SHIFT;
    } 
    else if (s == "bank") {
      if (argc < 2) {
        object_post((t_object *)T, "please add up, down, left or right.");
        return T;
      }
      else {
        std::string s; s = atom_getsym(argv + 1)->s_name;
        if (s == "left") {
          T->ID = B_SELECT_LEFT;
        }
        else if (s == "right") {
          T->ID = B_SELECT_RIGHT;
        }
        else if (s == "up") {
          T->ID = B_SELECT_UP;
        }
        else if (s == "down") {
          T->ID = B_SELECT_DOWN;
        }
        else {
          T->ID = B_INVALID;
        }
      }
    }
    else if (s == "tap") {
      T->ID = B_TAP;
    }
    else if (s == "nudge-") {
      T->ID = B_NUDGE_MIN;
    }
    else if (s == "nudge+") {
      T->ID = B_NUDGE_PLUS;
    }
    else if (s == "clip") {
      T->ID = B_CLIP;
    }
    else if (s == "device") {
      T->ID = B_DEVICE;
    } 
    else if (s == "left") {
      T->ID = B_ARROW_LEFT;
    }
    else if (s == "right") {
      T->ID = B_ARROW_RIGHT;
    }
    else if (s == "detail") {
      T->ID = B_DETAIL;
    }
    else if (s == "quantize") {
      T->ID = B_QUANTIZE;
    }
    else if (s == "midi") {
      T->ID = B_OVERDUB;
    }
    else if (s == "metronome") {
      T->ID = B_METRONOME;
    }
    else if (s == "play") {
      T->ID = B_PLAY;
    } 
  }

  if (T->ID == B_INVALID) {
    object_post((t_object *)T, "Unknown Button");
    return T;
  }

  T->intOut = intout((t_object *)T);
  ButtonManager.add(T);
  return T;
}

void CLASSMETHOD(Free)(IMPORT_T) {
  ButtonManager.remove(T);
}

void CLASSMETHOD(Send)(IMPORT_T, long n) {
  if (!T->active) return;
  outlet_int(T->intOut, n);
}

void CLASSMETHOD(Toggle)(IMPORT_T, long n) {
  if (n == 0) T->active = false;
  else T->active = true;
}

void CLASSMETHOD(SetState)(IMPORT_T, long n)
{
  if (T->ID == B_INVALID) return;
  ButtonManager.setValue(T->ID, n == 0 ? false : true);
  int note = ButtonToNote(T->ID);
  int channel = ButtonToChannel(T->ID);
  int value = ButtonManager.getValue(T->ID);
  apc40SendNoteOn(APC40, channel, note, value);
}


int ButtonToChannel(BUTTON b) {
  switch (b) {
  case B_STOP1: return 1;
  case B_STOP2: return 2;
  case B_STOP3: return 3;
  case B_STOP4: return 4;
  case B_STOP5: return 5;
  case B_STOP6: return 6;
  case B_STOP7: return 7;
  case B_STOP8: return 8;
  case B_TRACK1: return 1;
  case B_TRACK2: return 2;
  case B_TRACK3: return 3;
  case B_TRACK4: return 4;
  case B_TRACK5: return 5;
  case B_TRACK6: return 6;
  case B_TRACK7: return 7;
  case B_TRACK8: return 8;
  case B_TRACKM: return 1;
  case B_ACT1: return 1;
  case B_ACT2: return 2;
  case B_ACT3: return 3;
  case B_ACT4: return 4;
  case B_ACT5: return 5;
  case B_ACT6: return 6;
  case B_ACT7: return 7;
  case B_ACT8: return 8;
  case B_SOLO1: return 1;
  case B_SOLO2: return 2;
  case B_SOLO3: return 3;
  case B_SOLO4: return 4;
  case B_SOLO5: return 5;
  case B_SOLO6: return 6;
  case B_SOLO7: return 7;
  case B_SOLO8: return 8;
  case B_REC1: return 1;
  case B_REC2: return 2;
  case B_REC3: return 3;
  case B_REC4: return 4;
  case B_REC5: return 5;
  case B_REC6: return 6;
  case B_REC7: return 7;
  case B_REC8: return 8;
  default: return 1;
  }
}

int ButtonToNote(BUTTON b) {
  switch (b) {
    case B_SCENE1      : return 0x52;
    case B_SCENE2      : return 0x53;
    case B_SCENE3      : return 0x54;
    case B_SCENE4      : return 0x55;
    case B_SCENE5      : return 0x56;
    case B_STOP1       : return 0x34;
    case B_STOP2       : return 0x34;
    case B_STOP3       : return 0x34;
    case B_STOP4       : return 0x34;
    case B_STOP5       : return 0x34;
    case B_STOP6       : return 0x34;
    case B_STOP7       : return 0x34;
    case B_STOP8       : return 0x34;
    case B_STOPALL     : return 0x51;
    case B_TRACK1      : return 0x33;
    case B_TRACK2      : return 0x33;
    case B_TRACK3      : return 0x33;
    case B_TRACK4      : return 0x33;
    case B_TRACK5      : return 0x33;
    case B_TRACK6      : return 0x33;
    case B_TRACK7      : return 0x33;
    case B_TRACK8      : return 0x33;
    case B_TRACKM      : return 0x50;
    case B_ACT1        : return 0x32;
    case B_ACT2        : return 0x32;
    case B_ACT3        : return 0x32;
    case B_ACT4        : return 0x32;
    case B_ACT5        : return 0x32;
    case B_ACT6        : return 0x32;
    case B_ACT7        : return 0x32;
    case B_ACT8        : return 0x32;
    case B_SOLO1       : return 0x31;
    case B_SOLO2       : return 0x31;
    case B_SOLO3       : return 0x31;
    case B_SOLO4       : return 0x31;
    case B_SOLO5       : return 0x31;
    case B_SOLO6       : return 0x31;
    case B_SOLO7       : return 0x31;
    case B_SOLO8       : return 0x31;
    case B_REC1        : return 0x30;
    case B_REC2        : return 0x30;
    case B_REC3        : return 0x30;
    case B_REC4        : return 0x30;
    case B_REC5        : return 0x30;
    case B_REC6        : return 0x30;
    case B_REC7        : return 0x30;
    case B_REC8        : return 0x30;
    case B_PAN         : return 0x57;
    case B_SENDA       : return 0x58;
    case B_SENDB       : return 0x59;
    case B_SENDC       : return 0x5A;
    case B_SHIFT       : return 0x62;
    case B_SELECT_UP   : return 0x5E;
    case B_SELECT_DOWN : return 0x5F;
    case B_SELECT_LEFT : return 0x61;
    case B_SELECT_RIGHT: return 0x60;
    case B_TAP         : return 0x63;
    case B_NUDGE_MIN   : return 0x65;
    case B_NUDGE_PLUS  : return 0x64;
    case B_CLIP        : return 0x3A;
    case B_DEVICE      : return 0x3B;
    case B_ARROW_LEFT  : return 0x3C;
    case B_ARROW_RIGHT : return 0x3D;
    case B_DETAIL      : return 0x3E;
    case B_QUANTIZE    : return 0x3F;
    case B_OVERDUB     : return 0x40;
    case B_METRONOME   : return 0x41;
    case B_PLAY        : return 0x5B;
    case B_STOP        : return 0x5C;
    case B_REC         : return 0x5D;
    default            : return 0x00;
  }
}

BUTTON NoteToButton(int i) {
  switch (i) {
  case 0x52: return B_SCENE1;
  case 0x53: return B_SCENE2;
  case 0x54: return B_SCENE3;
  case 0x55: return B_SCENE4;
  case 0x56: return B_SCENE5;
  case 0x34: return B_STOP1;
  case 0x51: return B_STOPALL;
  case 0x33: return B_TRACK1;
  case 0x50: return B_TRACKM;
  case 0x32: return B_ACT1;
  case 0x31: return B_SOLO1;
  case 0x30: return B_REC1;
  case 0x57: return B_PAN;
  case 0x58: return B_SENDA;
  case 0x59: return B_SENDB;
  case 0x5A: return B_SENDC;
  case 0x62: return B_SHIFT;
  case 0x5E: return B_SELECT_UP;
  case 0x5F: return B_SELECT_DOWN;
  case 0x61: return B_SELECT_LEFT;
  case 0x60: return B_SELECT_RIGHT;
  case 0x63: return B_TAP;
  case 0x65: return B_NUDGE_MIN;
  case 0x64: return B_NUDGE_PLUS;
  case 0x3A: return B_CLIP;
  case 0x3B: return B_DEVICE;
  case 0x3C: return B_ARROW_LEFT;
  case 0x3D: return B_ARROW_RIGHT;
  case 0x3E: return B_DETAIL;
  case 0x3F: return B_QUANTIZE;
  case 0x40: return B_OVERDUB;
  case 0x41: return  B_METRONOME;
  case 0x5B: return B_PLAY;
  case 0x5C: return B_STOP;
  case 0x5D: return B_REC;
  default: return B_INVALID;
  }
}