#include "ceguirenderingsurface.hpp"
VALUE rb_cCeguiRenderingSurface;

#define _self wrap<CEGUI::RenderingSurface*>(self)

void Init_CeguiRenderingSurface(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
#endif
	rb_cCeguiRenderingSurface = rb_define_class_under(rb_mCegui,"RenderingSurface",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderingSurface);
}
