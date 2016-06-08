#include "p_receive.h"

CREATECLASSPTR;

void * CLASSMETHOD(New)() {
  DECLARE_T;
  T->s_value = 0;
  return T;
}

void CLASSMETHOD(Int)(IMPORT_T, long n) {
  T->s_value = n;
}

void CLASSMETHOD(Bang)(IMPORT_T) {
  post("in value is %ld", T->s_value);
}