#include "Slider.h"
#include <string>

std::vector<slider*> Sliders;

CREATECLASSPTR;

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv) {
  DECLARE_T;

  if (argc < 1) {
    object_post((t_object *)T, "I need a slider name as first argument");
    return T;
  }

  if ((argv)->a_type == A_SYM) {
    std::string s; s = atom_getsym(argv)->s_name;
    if (s == "master") T->ID = S_MASTER;
    else if (s == "pan") T->ID = S_PAN;
    else object_post((t_object *)T, "Unknown Slider name");
  }
  else {
    int i = atom_getlong(argv);
    switch (i) {
      case 1: T->ID = S_1; break;
      case 2: T->ID = S_2; break;
      case 3: T->ID = S_3; break;
      case 4: T->ID = S_4; break;
      case 5: T->ID = S_5; break;
      case 6: T->ID = S_6; break;
      case 7: T->ID = S_7; break;
      case 8: T->ID = S_8; break;
      default: object_post((t_object *)T, "Unknown Slider ID");
    }
  }

  T->intOut = intout((t_object *)T);

  Sliders.push_back(T);

  return T;
}

void CLASSMETHOD(Free)(IMPORT_T) {
  for (auto it = Sliders.begin(); it != Sliders.end(); it++) {
    if (*it == T) {
      Sliders.erase(it);
      return;
    }
  }
}

void CLASSMETHOD(Send)(IMPORT_T, long n) {
  outlet_int(T->intOut, n);
}