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