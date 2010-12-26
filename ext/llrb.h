#ifndef _LLRB_H
#define _LLRB_H

#include <ruby.h>

extern VALUE cLLRB;
extern VALUE cLLRBContext;
extern VALUE cLLRBModule;

#define LLRB_CONTEXT(value) ((LLVMContext*)DATA_PTR(value))

#endif