#include "ext.h"
#include "apc40.h"
#include "ClipLauncher.h"
#include "Slider.h"
#include "Knob.h"
#include "Button.h"

bool loaded = false;

void C74_EXPORT ext_main(void * r) {
  if (loaded) return;
  loaded = true;

  {
    #undef ClassName
    #define ClassName apc40
    SETUP("apc40", CLASSMETHOD(New), CLASSMETHOD(Free));

    class_addmethod(CLASS, (method)CLASSMETHOD(Reset), "reset", 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(inletInt), "int", A_LONG, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(ClipLed), "clipled", A_GIMME, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(ClipMode), "clipmode", A_GIMME, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(ClipRow), "cliprow", A_GIMME, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(KnobStyle), "knobstyle", A_GIMME, 0);
    REGISTER_BOX;
  }

  {
    #undef ClassName
    #define ClassName clipLauncher
    SETUP("apcClip", CLASSMETHOD(New), CLASSMETHOD(Free));
    class_addmethod(CLASS, (method)CLASSMETHOD(Toggle), "toggle", A_LONG, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(Set), "set", A_LONG, 0);
    REGISTER_BOX;
  }

  {
    #undef ClassName
    #define ClassName slider
    SETUP("apcSlider", CLASSMETHOD(New), CLASSMETHOD(Free));
    class_addmethod(CLASS, (method)CLASSMETHOD(Toggle), "toggle", A_LONG, 0);
    REGISTER_BOX;
  }

  {
    #undef ClassName
    #define ClassName button
    SETUP("apcButton", CLASSMETHOD(New), CLASSMETHOD(Free));
    class_addmethod(CLASS, (method)CLASSMETHOD(Toggle), "toggle", A_LONG, 0);
    REGISTER_BOX;
  }

  {
  #undef ClassName
  #define ClassName knob
    SETUP("apcKnob", CLASSMETHOD(New), CLASSMETHOD(Free));
    class_addmethod(CLASS, (method)CLASSMETHOD(Toggle), "toggle", A_LONG, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(inletInt), "int", A_LONG, 0);
    REGISTER_BOX;
  }


  post("APC DLL loaded (version 5)");
}