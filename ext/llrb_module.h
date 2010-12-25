#ifndef _LLRB_MODULE_H
#define _LLRB_MODULE_H

#include <ruby.h>

VALUE llrb_module_allocate(VALUE klass);
VALUE llrb_module_initialize(VALUE self, VALUE rname);

#endif