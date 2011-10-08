#include "ceguirendertarget.hpp"
#include "ceguirect.hpp"
VALUE rb_cCeguiRenderTarget;

#define _self wrap<CEGUI::RenderTarget*>(self)

macro_attr(RenderTarget,Area,CEGUI::Rectf)

void Init_CeguiRenderTarget(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiRenderTarget,"area",1,1);
#endif
	rb_cCeguiRenderTarget = rb_define_class_under(rb_mCegui,"RenderTarget",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderTarget);
	
	rb_define_attr_method(rb_cCeguiRenderTarget,"area",CeguiRenderTarget_getArea,CeguiRenderTarget_setArea);
}
