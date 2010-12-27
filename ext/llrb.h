#ifndef _LLRB_H
#define _LLRB_H

#include <ruby.h>

extern VALUE cLLRB;
extern VALUE cLLRBContext;
extern VALUE cLLRBModule;
extern VALUE cLLRBType;

#define LLRB_CONTEXT(value) ((LLVMContext*)DATA_PTR(value))

#define CHECK_TYPE(val, klass)\
  if(!rb_obj_is_kind_of(val, klass)) {\
    rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)", rb_obj_classname(val), rb_class2name(klass));\
  }


#endif