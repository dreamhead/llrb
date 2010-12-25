#include <ruby.h>
#include "llrb_module.h"

VALUE cLLRB = Qnil;
VALUE cLLRBModule = Qnil;

void Init_llrb() {
	cLLRB = rb_define_module("LLRB");
	cLLRBModule = rb_define_class_under(cLLRB, "Module", rb_cObject);
	rb_define_alloc_func(cLLRBModule, llrb_module_allocate);
	rb_define_method(cLLRBModule, "initialize", llrb_module_initialize, 1);
}