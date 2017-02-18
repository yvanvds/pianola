#pragma once
#include "ext.h"
#include <vector>

#undef ClassName
#define ClassName slider
#include "defines.h"

CREATESTRUCT(
  SLIDER ID;
  bool active;
  void * intOut;
);

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(Free)(IMPORT_T);
void CLASSMETHOD(Toggle)(IMPORT_T, long n);

void CLASSMETHOD(Send)(IMPORT_T, long n);

extern std::vector<slider*> Sliders;