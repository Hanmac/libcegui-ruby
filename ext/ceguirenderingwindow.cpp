#include "ceguirenderingsurface.hpp"
#include "ceguirenderingwindow.hpp"
#include "ceguiexception.hpp"
#include "ceguivector2.hpp"
#include "ceguivector3.hpp"
#include "ceguisize.hpp"
#include "ceguiquaternion.hpp"

#define _self wrap<CEGUI::RenderingWindow*>(self)
VALUE rb_cCeguiRenderingWindow;

namespace CeguiRenderingWindow {

macro_attr(Position,CEGUI::Vector2f)
macro_attr(Rotation,CEGUI::Quaternion)
macro_attr(Pivot,CEGUI::Vector3f)
macro_attr(Size,CEGUI::Sizef)

}

void Init_CeguiRenderingWindow(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiRenderingSurface = rb_define_class_under(rb_mCegui,"RenderingSurface",rb_cObject);
	rb_define_attr(rb_cCeguiRenderingWindow,"position",1,1);
	rb_define_attr(rb_cCeguiRenderingWindow,"rotation",1,1);
	rb_define_attr(rb_cCeguiRenderingWindow,"pivot",1,1);
	rb_define_attr(rb_cCeguiRenderingWindow,"size",1,1);
#endif
	using namespace CeguiRenderingWindow;
	rb_cCeguiRenderingWindow = rb_define_class_under(rb_mCegui,"RenderingWindow",rb_cCeguiRenderingSurface);


	rb_define_attr_method(rb_cCeguiRenderingWindow,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cCeguiRenderingWindow,"rotation",_getRotation,_setRotation);
	rb_define_attr_method(rb_cCeguiRenderingWindow,"pivot",_getPivot,_setPivot);
	rb_define_attr_method(rb_cCeguiRenderingWindow,"size",_getSize,_setSize);
}
