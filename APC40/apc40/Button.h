#pragma once
#include "ext.h"
#include <vector>

#undef ClassName
#define ClassName button
#include "defines.h"

CREATESTRUCT(
  BUTTON ID;
  bool active;

  void *intOut;
);

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(Free)(IMPORT_T);
void CLASSMETHOD(Toggle)(IMPORT_T, long n);
void CLASSMETHOD(SetState)(IMPORT_T, long n);

void CLASSMETHOD(Send)(IMPORT_T, long n);

int ButtonToNote(BUTTON b);
int ButtonToChannel(BUTTON b);
BUTTON NoteToButton(int i);