#include <ruby.h>
#include "llrb.h"

#undef NORETURN
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"

using namespace llvm;

extern "C" {
    
VALUE llrb_module_allocate(VALUE klass) {
    return Data_Wrap_Struct(klass, NULL, NULL, NULL);
}

#define CHECK_TYPE(val, klass)\
  if(!rb_obj_is_kind_of(val, klass)) {\
    rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)", rb_obj_classname(val), rb_class2name(klass));\
  }


VALUE llrb_module_initialize(VALUE self, VALUE name, VALUE context) {
    Check_Type(name, T_STRING);
	CHECK_TYPE(context, cLLRBContext);
    
	LLVMContext* c = LLRB_CONTEXT(context);
    DATA_PTR(self) = new Module(StringValuePtr(name), *c);
    return self;
}

}