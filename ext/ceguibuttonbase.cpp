#include "ceguibuttonbase.hpp"

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::ButtonBase*>(self)
VALUE rb_cCeguiButtonBase;


/*
*/
VALUE CeguiButtonBase_isPushed(VALUE self)
{
	return RBOOL(_self->isPushed());
}

/*
*/
VALUE CeguiButtonBase_isHovering(VALUE self)
{
	return RBOOL(_self->isHovering());
}

/*
*/
void Init_CeguiButtonBase(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

#endif

	rb_cCeguiButtonBase = rb_define_class_under(rb_mCegui,"ButtonBase",rb_cCeguiWindow);
	
	rb_define_method(rb_cCeguiButtonBase,"pushed?",RUBY_METHOD_FUNC(CeguiButtonBase_isPushed),1);
	rb_define_method(rb_cCeguiButtonBase,"hovering?",RUBY_METHOD_FUNC(CeguiButtonBase_isHovering),1);
}
