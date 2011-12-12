#include "ceguieventargs.hpp"
#include "ceguiwindow.hpp"
#define _self wrap<CEGUI::WindowEventArgs*>(self)

VALUE rb_cCeguiWindowEventArgs;

void Init_CeguiWindowEventArgs(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
#endif
	rb_cCeguiWindowEventArgs = rb_define_class_under(rb_cCeguiWindow,"EventArgs",rb_cCeguiEventArgs);
	rb_undef_alloc_func(rb_cCeguiWindowEventArgs);
}


