#include <ruby.h>
#include "llrb.h"

#undef NORETURN
#include "llvm/LLVMContext.h"
#include "llvm/Type.h"
#include "llvm/DerivedTypes.h"

using namespace llvm;

extern "C" {
	
VALUE llvm_type_wrap(const Type* type) {
    return Data_Wrap_Struct(cLLRBType, NULL, NULL, const_cast<Type*>(type));
}

VALUE llvm_type_int32(VALUE self, VALUE context) {
    CHECK_TYPE(context, cLLRBContext);
    LLVMContext* c = LLRB_CONTEXT(context);
    return llvm_type_wrap(Type::getInt32Ty(*c));
}	

}