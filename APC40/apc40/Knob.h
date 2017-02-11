#pragma once
#include "ext.h"
#include <vector>

#undef ClassName
#define ClassName knob
#include "defines.h"

CREATESTRUCT(
  KNOB ID;
  KNOB_STYLE style;

  void * intOut;
);

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(Free)(IMPORT_T);

void CLASSMETHOD(Send)(IMPORT_T, long n);

