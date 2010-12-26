#include <ruby.h>
#include "llrb_context.h"
#include "llrb_module.h"

VALUE cLLRB = Qnil;
VALUE cLLRBContext = Qnil;
VALUE cLLRBModule = Qnil;

void Init_llrb() {
	cLLRB = rb_define_module("LLRB");
	
	cLLRBContext = rb_define_class_under(cLLRB, "Context", rb_cObject);
	rb_define_method(rb_cObject, "get_global_context", llrb_get_global_context, 0);
	
	cLLRBModule = rb_define_class_under(cLLRB, "Module", rb_cObject);
	rb_define_alloc_func(cLLRBModule, llrb_module_allocate);
	rb_define_method(cLLRBModule, "initialize", llrb_module_initialize, 2);
}