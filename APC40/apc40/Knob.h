#pragma once
#include "ext.h"
#include <vector>

#undef ClassName
#define ClassName knob
#include "defines.h"

CREATESTRUCT(
  KNOB ID;
  KNOB_STYLE style;

  bool active;

  void * intOut;
);

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(Free)(IMPORT_T);

void CLASSMETHOD(Toggle)(IMPORT_T, long n);
void CLASSMETHOD(inletInt)(IMPORT_T, long n);

void CLASSMETHOD(Send)(IMPORT_T, long n);

int GetKnobCTRL(KNOB ID);
int GetKnobLedCTRL(KNOB ID);
int GetKnobStyleCTRL(KNOB_STYLE);