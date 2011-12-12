/*
 * ceguilistheadersegment.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#include "ceguiwindow.hpp"
#include "ceguiimage.hpp"

#define _self wrap<CEGUI::ListHeaderSegment*>(self)
VALUE rb_cCeguiListHeaderSegment;

namespace CeguiListHeaderSegment {

macro_attr_bool(SizingEnabled)
macro_attr_bool(DragMovingEnabled)

macro_attr_bool(Clickable)

macro_attr(SizingCursorImage, CEGUI::Image*)
macro_attr(MovingCursorImage,CEGUI::Image*)
//macro_attr(TabHeight,CEGUI::UDim)
//macro_attr(TabTextPadding,CEGUI::UDim)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::ListHeaderSegment::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

}
/*
*/
void Init_CeguiListHeaderSegment(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiListHeader = rb_define_class_under(rb_mCegui,"ListHeader",rb_cCeguiWindow);

	rb_define_attr(rb_cCeguiListHeaderSegment,"sizingEnabled",1,1);
	rb_define_attr(rb_cCeguiListHeaderSegment,"dragMovingEnabled",1,1);
	rb_define_attr(rb_cCeguiListHeaderSegment,"clickable",1,1);

	rb_define_attr(rb_cCeguiListHeaderSegment,"sizingCursorImage",1,1);
	rb_define_attr(rb_cCeguiListHeaderSegment,"movingCursorImage",1,1);
#endif
	using namespace CeguiListHeaderSegment;

	rb_cCeguiListHeaderSegment = rb_define_class_under(rb_cCeguiListHeader,"Segment",rb_cCeguiWindow);

	rb_define_attr_method(rb_cCeguiListHeaderSegment,"sizingEnabled",_getSizingEnabled,_setSizingEnabled);
	rb_define_attr_method(rb_cCeguiListHeaderSegment,"dragMovingEnabled",_getDragMovingEnabled,_setDragMovingEnabled);
	rb_define_attr_method(rb_cCeguiListHeaderSegment,"clickable",_getClickable,_setClickable);

	rb_define_attr_method(rb_cCeguiListHeaderSegment,"sizingCursorImage",_getSizingCursorImage,_setSizingCursorImage);
	rb_define_attr_method(rb_cCeguiListHeaderSegment,"movingCursorImage",_getMovingCursorImage,_setMovingCursorImage);


	rb_define_singleton_method(rb_cCeguiListHeaderSegment,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiListHeaderSegment,"WidgetTypeName",wrap(CEGUI::ListHeaderSegment::WidgetTypeName));
	rb_define_const(rb_cCeguiListHeaderSegment,"EventNamespace",wrap(CEGUI::ListHeaderSegment::EventNamespace));


}









