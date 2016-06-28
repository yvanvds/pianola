
#include "p_send.h"
#include "p_receive.h"

bool loaded = false;

void C74_EXPORT ext_main(void * r) {
  if (loaded) return;
  loaded = true;

  {
    #undef ClassName
    #define ClassName p_receive
    SETUP("p-receive", CLASSMETHOD(New), NULL);
    
    class_addmethod(CLASS, (method)CLASSMETHOD(Int), "int", A_LONG, 0);
    
    class_addmethod(CLASS, (method)CLASSMETHOD(Bang), "bang", 0);

    REGISTER_BOX;
  }

  {
    #undef ClassName
    #define ClassName p_send
    SETUP("p-send", CLASSMETHOD(New), NULL);

    class_addmethod(CLASS, (method)CLASSMETHOD(Joint    ), "joint"    , A_GIMME, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(Light    ), "light"    , A_GIMME, 0);
    class_addmethod(CLASS, (method)CLASSMETHOD(HeadLight), "headlight", A_GIMME, 0);

    REGISTER_BOX;
  }


  post("Pianola DLL Loaded");
}