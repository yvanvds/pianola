#pragma once
#include "ext.h"

#undef ClassName
#define ClassName p_send
#include "defines.h"
#include "Enums.h"

#include "Network.h"

CREATESTRUCT(
  IDENTITY   id       ;
  ROBOT_PART part     ;
  BEHAVIOUR  behaviour;
  bool valid;
);

void * CLASSMETHOD(New  )(t_symbol * s, long argc, t_atom * argv);
void   CLASSMETHOD(Int  )(IMPORT_T, long  n);
void   CLASSMETHOD(Float)(IMPORT_T, float f);
void   CLASSMETHOD(Bang )(IMPORT_T         );