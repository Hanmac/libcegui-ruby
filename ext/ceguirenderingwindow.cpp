#include "ceguirenderingsurface.hpp"
#include "ceguirenderingwindow.hpp"

#include "ceguivector2.hpp"
#include "ceguivector3.hpp"
#include "ceguisize.hpp"

#define _self wrap<CEGUI::RenderingWindow*>(self)

macro_attr(RenderingWindow,Position,CEGUI::Vector2f)
macro_attr(RenderingWindow,Rotation,CEGUI::Quaternion)
macro_attr(RenderingWindow,Pivot,CEGUI::Vector3f)
macro_attr(RenderingWindow,Size,CEGUI::Sizef)

VALUE rb_cCeguiRenderingWindow;
void Init_CeguiRenderingWindow(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiRenderingSurface = rb_define_class_under(rb_mCegui,"RenderingSurface",rb_cObject);
	rb_define_attr(rb_cCeguiRenderingWindow,"position",1,1);
	rb_define_attr(rb_cCeguiRenderingWindow,"rotation",1,1);
	rb_define_attr(rb_cCeguiRenderingWindow,"pivot",1,1);
	rb_define_attr(rb_cCeguiRenderingWindow,"size",1,1);
#endif
	rb_cCeguiRenderingWindow = rb_define_class_under(rb_mCegui,"RenderingWindow",rb_cCeguiRenderingSurface);


	rb_define_attr_method(rb_cCeguiRenderingWindow,"position",CeguiRenderingWindow_getPosition,CeguiRenderingWindow_setPosition);
	rb_define_attr_method(rb_cCeguiRenderingWindow,"rotation",CeguiRenderingWindow_getRotation,CeguiRenderingWindow_setRotation);
	rb_define_attr_method(rb_cCeguiRenderingWindow,"pivot",CeguiRenderingWindow_getPivot,CeguiRenderingWindow_setPivot);
	rb_define_attr_method(rb_cCeguiRenderingWindow,"size",CeguiRenderingWindow_getSize,CeguiRenderingWindow_setSize);
}
