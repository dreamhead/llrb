#include <ruby.h>

#undef NORETURN
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"

using namespace llvm;

extern "C" {
	
VALUE llrb_module_allocate(VALUE klass) {
	return Data_Wrap_Struct(klass, NULL, NULL, NULL);
}

VALUE llrb_module_initialize(VALUE self, VALUE rname) {
  // Check_Type(rname, T_STRING);
  // DATA_PTR(self) = new Module(StringValuePtr(rname), getGlobalContext());
  return self;
}

}