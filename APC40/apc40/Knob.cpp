#include "Knob.h"
#include <string>
#include "KnobManager.h"

CREATECLASSPTR;

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv) {
  DECLARE_T;

  T->ID = K_INVALID;
  if (argc < 1) {
    object_post((t_object *)T, "I need a knob name as first argument");
    return T;
  }

  if ((argv)->a_type == A_SYM) {
    std::string s; s = atom_getsym(argv)->s_name;
    if (s == "cue") T->ID = K_CUE;
    else if (s == "track") {
      if (argc < 2) {
        object_post((t_object *)T, "I need the number of this track control");
        return T;
      }
      else {
        int v = (int)atom_getlong(argv + 1);
        switch (v) {
          case 1: T->ID = K_TRACK1; break;
          case 2: T->ID = K_TRACK2; break;
          case 3: T->ID = K_TRACK3; break;
          case 4: T->ID = K_TRACK4; break;
          case 5: T->ID = K_TRACK5; break;
          case 6: T->ID = K_TRACK6; break;
          case 7: T->ID = K_TRACK7; break;
          case 8: T->ID = K_TRACK8; break;
        }
      }
    } 
    else if (s == "device") {
      if (argc < 2) {
        object_post((t_object *)T, "I need the number of this device control");
        return T;
      }
      else {
        int v = (int)atom_getlong(argv + 1);
        switch (v) {
        case 1: T->ID = K_DEVICE1; break;
        case 2: T->ID = K_DEVICE2; break;
        case 3: T->ID = K_DEVICE3; break;
        case 4: T->ID = K_DEVICE4; break;
        case 5: T->ID = K_DEVICE5; break;
        case 6: T->ID = K_DEVICE6; break;
        case 7: T->ID = K_DEVICE7; break;
        case 8: T->ID = K_DEVICE8; break;
        }
      }
    }   
  }


  if (T->ID == K_INVALID) {
    object_post((t_object *)T, "Unknown Knob");
    return T;
  }

  T->intOut = intout((t_object *)T);
  KnobManager.add(T);
  return T;
}

void CLASSMETHOD(Free)(IMPORT_T) {
  KnobManager.remove(T);
}

void CLASSMETHOD(Send)(IMPORT_T, long n) {
  outlet_int(T->intOut, n);
}

int GetKnobCTRL(KNOB ID) {
  switch (ID) {
    case K_DEVICE1: return 0x10; break;
    case K_DEVICE2: return 0x11; break;
    case K_DEVICE3: return 0x12; break;
    case K_DEVICE4: return 0x13; break;
    case K_DEVICE5: return 0x14; break;
    case K_DEVICE6: return 0x15; break;
    case K_DEVICE7: return 0x16; break;
    case K_DEVICE8: return 0x17; break;
    case K_TRACK1 : return 0x30; break;
    case K_TRACK2 : return 0x31; break;
    case K_TRACK3 : return 0x32; break;
    case K_TRACK4 : return 0x33; break;
    case K_TRACK5 : return 0x34; break;
    case K_TRACK6 : return 0x35; break;
    case K_TRACK7 : return 0x36; break;
    case K_TRACK8 : return 0x37; break;
  }
  return 0x0;
}

int GetKnobLedCTRL(KNOB ID) {
  switch (ID) {
    case K_DEVICE1: return 0x18; break;
    case K_DEVICE2: return 0x19; break;
    case K_DEVICE3: return 0x1A; break;
    case K_DEVICE4: return 0x1B; break;
    case K_DEVICE5: return 0x1C; break;
    case K_DEVICE6: return 0x1D; break;
    case K_DEVICE7: return 0x1E; break;
    case K_DEVICE8: return 0x1F; break;
    case K_TRACK1: return 0x38; break;
    case K_TRACK2: return 0x39; break;
    case K_TRACK3: return 0x3A; break;
    case K_TRACK4: return 0x3B; break;
    case K_TRACK5: return 0x3C; break;
    case K_TRACK6: return 0x3D; break;
    case K_TRACK7: return 0x3E; break;
    case K_TRACK8: return 0x3F; break;
  }
  return 0x0;
}

int GetKnobStyleCTRL(KNOB_STYLE style) {
  switch (style) {
  case KS_OFF   : return 0;
  case KS_SINGLE: return 1;
  case KS_VOLUME: return 2;
  case KS_PAN   : return 3;
  default       : return 0;
  }
}