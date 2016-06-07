#pragma once
#include "ext.h"


#undef ClassName
#define ClassName p_receive
#include "defines.h"

CREATESTRUCT(
  long s_value;
  long s2_value;
);

void * CLASSMETHOD(New)();


void CLASSMETHOD(Int)(IMPORT_T, long n);

void CLASSMETHOD(Bang)(IMPORT_T);