#pragma once
#include "ext.h"
#include "apcMemory.h"

#undef ClassName
#define ClassName apc40
#include "defines.h"



CREATESTRUCT(
  apcMemory memory ;
  MIDI_MESSAGE curMessage;
  int curChannel;
  int curStep;
  int curVal1;
  int curVal2;

  // outlets
  void * intOut;
  void * messageOut;
);


// construct & destruct
void * CLASSMETHOD(New)();
void CLASSMETHOD(Free)(IMPORT_T);

// incoming messages
void CLASSMETHOD(Reset)(IMPORT_T);
void CLASSMETHOD(inletInt)(IMPORT_T, long n);
void CLASSMETHOD(ClipLed)(IMPORT_T, t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(ClipMode)(IMPORT_T, t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(ClipRow)(IMPORT_T, t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(KnobStyle)(IMPORT_T, t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(ActivateButton)(IMPORT_T, t_symbol * s, long argc, t_atom *argv);

// internal messages
void CLASSMETHOD(HandleNoteOn)(IMPORT_T);
void CLASSMETHOD(HandleCTRL)(IMPORT_T);
void CLASSMETHOD(HandleNoteOff)(IMPORT_T);

void CLASSMETHOD(SendNoteOn)(IMPORT_T, int channel, int note, int velocity);
void CLASSMETHOD(SendCTRL)(IMPORT_T, int channel, int ctrl, int value);

extern apc40 * APC40;