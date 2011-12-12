#include "ceguieventargs.hpp"
#include "ceguievent.hpp"
#define _self wrap<CEGUI::EventArgs*>(self)

VALUE rb_cCeguiEventArgs;

VALUE CeguiEventArgs_alloc(VALUE self)
{
	return wrap(new CEGUI::EventArgs);
}

void Init_CeguiEventArgs(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_cCeguiEvent = rb_define_class_under(rb_mCegui,"Event",rb_cObject);
#endif
	rb_cCeguiEventArgs = rb_define_class_under(rb_cCeguiEvent,"Args",rb_cObject);
//	rb_undef_alloc_func(rb_cCeguiEventArgs);
	rb_define_alloc_func(rb_cCeguiEventArgs,CeguiEventArgs_alloc);
}
