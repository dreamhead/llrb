#include <ruby.h>
#include "llrb.h"
#include "llvm/LLVMContext.h"

using namespace llvm;

extern "C" {

VALUE llrb_get_global_context(VALUE self) {
    LLVMContext& context = getGlobalContext();
    return Data_Wrap_Struct(cLLRBContext, NULL, NULL, &context);
}

}