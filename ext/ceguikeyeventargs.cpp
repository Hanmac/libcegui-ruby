#include "ceguiwindoweventargs.hpp"
#include "ceguiwindow.hpp"
#define _self wrap<CEGUI::KeyEventArgs*>(self)

VALUE rb_cCeguiKeyEventArgs;

VALUE rb_mCeguiKey;

/*
*/
VALUE CeguiKeyEventArgs_getCodepoint(VALUE self)
{
	return UINT2NUM(_self->codepoint);
}

void Init_CeguiKeyEventArgs(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
#endif
	rb_mCeguiKey = rb_define_module_under(rb_mCegui,"Key");
	rb_cCeguiKeyEventArgs = rb_define_class_under(rb_mCeguiKey,"EventArgs",rb_cCeguiWindowEventArgs);

	

	rb_define_method(rb_cCeguiKeyEventArgs,"codepoint",RUBY_METHOD_FUNC(CeguiKeyEventArgs_getCodepoint),0);

	rb_undef_alloc_func(rb_cCeguiWindowEventArgs);
}


