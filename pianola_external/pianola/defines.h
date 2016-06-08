#pragma once

#define CONCAT_NX(A, B) A ## B
#define CONCAT(A, B) CONCAT_NX(A, B)

#define CLASS CONCAT(ClassName, Class)
#define CLASSMETHOD(name) CONCAT(ClassName, name)

#define CREATESTRUCT(content) typedef struct ClassName { t_object obj; content } ClassName; extern t_class * CLASS
#define CREATECLASSPTR t_class * CLASS
#define DECLARE_T ClassName * T = (ClassName*)object_alloc(CLASS)
#define IMPORT_T ClassName * T

#define SETUP(name, funcNew, funcFree) CLASS = class_new(name, (method)funcNew, (method)funcFree, sizeof(ClassName), 0L, A_GIMME, 0);
#define REGISTER_BOX class_register(CLASS_BOX, CLASS)
#define REGISTER_NOBOX class_register(CLASS_NOBOX, CLASS)

#define PROJECTNAME "/pianola";

