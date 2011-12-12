/*
 * ceguidragcontainer.cpp
 *
 *  Created on: 04.12.2011
 *      Author: hanmac
 */

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::DragContainer*>(self)
VALUE rb_cCeguiDragContainer;

namespace CeguiDragContainer {

macro_attr_bool(DraggingEnabled)
macro_attr_bool(UsingFixedDragOffset)

macro_attr(PixelDragThreshold,float)
macro_attr(DragAlpha,float)
macro_attr(DragCursorImage,CEGUI::Image*)
macro_attr(FixedDragOffset,CEGUI::UVector2)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	if(argc==2)
		return rb_call_super(2,argv);
	else{
		rb_scan_args(argc, argv, "01",&name);
		VALUE result[2];
		result[0]=wrap(CEGUI::String(CEGUI::DragContainer::WidgetTypeName));
		result[1]=name;
		return rb_call_super(2,result);
	}
}

}

/*
*/
void Init_CeguiDragContainer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);


	rb_define_attr(rb_cCeguiDragContainer,"draggingEnabled",1,1);
	rb_define_attr(rb_cCeguiDragContainer,"usingFixedDragOffset",1,1);

	rb_define_attr(rb_cCeguiDragContainer,"pixelDragThreshold",1,1);
	rb_define_attr(rb_cCeguiDragContainer,"dragAlpha",1,1);
	rb_define_attr(rb_cCeguiDragContainer,"dragCursorImage",1,1);
	rb_define_attr(rb_cCeguiDragContainer,"fixedDragOffset",1,1);


#endif
	using namespace CeguiDragContainer;

	rb_cCeguiDragContainer = rb_define_class_under(rb_mCegui,"DragContainer",rb_cCeguiWindow);

	rb_define_attr_method(rb_cCeguiDragContainer,"draggingEnabled",_getDraggingEnabled,_setDraggingEnabled);
	rb_define_attr_method(rb_cCeguiDragContainer,"usingFixedDragOffset",_getUsingFixedDragOffset,_setUsingFixedDragOffset);

	rb_define_attr_method(rb_cCeguiDragContainer,"pixelDragThreshold",_getPixelDragThreshold,_setPixelDragThreshold);
	rb_define_attr_method(rb_cCeguiDragContainer,"dragAlpha",_getDragAlpha,_setDragAlpha);
	rb_define_attr_method(rb_cCeguiDragContainer,"dragCursorImage",_getDragCursorImage,_setDragCursorImage);
	rb_define_attr_method(rb_cCeguiDragContainer,"fixedDragOffset",_getFixedDragOffset,_setFixedDragOffset);

	rb_define_singleton_method(rb_cCeguiDragContainer,"new",RUBY_METHOD_FUNC(_new),-1);


	rb_define_const(rb_cCeguiDragContainer,"EventNamespace",wrap(CEGUI::DragContainer::EventNamespace));
	rb_define_const(rb_cCeguiDragContainer,"WidgetTypeName",wrap(CEGUI::DragContainer::WidgetTypeName));

	rb_define_const(rb_cCeguiDragContainer,"EventDragStarted",wrap(CEGUI::DragContainer::EventDragStarted));
	rb_define_const(rb_cCeguiDragContainer,"EventDragEnded",wrap(CEGUI::DragContainer::EventDragEnded));
	rb_define_const(rb_cCeguiDragContainer,"EventDragPositionChanged",wrap(CEGUI::DragContainer::EventDragPositionChanged));
	rb_define_const(rb_cCeguiDragContainer,"EventDragEnabledChanged",wrap(CEGUI::DragContainer::EventDragEnabledChanged));
	rb_define_const(rb_cCeguiDragContainer,"EventDragAlphaChanged",wrap(CEGUI::DragContainer::EventDragAlphaChanged));
	rb_define_const(rb_cCeguiDragContainer,"EventDragMouseCursorChanged",wrap(CEGUI::DragContainer::EventDragMouseCursorChanged));
	rb_define_const(rb_cCeguiDragContainer,"EventDragThresholdChanged",wrap(CEGUI::DragContainer::EventDragThresholdChanged));
	rb_define_const(rb_cCeguiDragContainer,"EventDragDropTargetChanged",wrap(CEGUI::DragContainer::EventDragDropTargetChanged));
}
