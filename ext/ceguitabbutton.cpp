/*
 * ceguitabbutton.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::TabButton*>(self)
VALUE rb_cCeguiTabButton;

namespace CeguiTabButton {

macro_attr_bool(Selected)
macro_attr(TargetWindow,CEGUI::Window*)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::TabButton::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

}
/*
*/
void Init_CeguiTabButton(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiButtonBase = rb_define_class_under(rb_mCegui,"ButtonBase",rb_cCeguiButtonBase);

	rb_define_attr(rb_cCeguiTabButton,"selected",1,1);
	rb_define_attr(rb_cCeguiTabButton,"targetWindow",1,1);
#endif
	using namespace CeguiTabButton;

	rb_cCeguiTabButton = rb_define_class_under(rb_mCegui,"TabButton",rb_cCeguiButtonBase);

	rb_define_attr_method(rb_cCeguiTabButton,"selected",_getSelected,_setSelected);
	rb_define_attr_method(rb_cCeguiTabButton,"targetWindow",_getTargetWindow,_setTargetWindow);

	rb_define_singleton_method(rb_cCeguiTabButton,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiTabButton,"WidgetTypeName",wrap(CEGUI::TabButton::WidgetTypeName));
	rb_define_const(rb_cCeguiTabButton,"EventNamespace",wrap(CEGUI::TabButton::EventNamespace));

	rb_define_const(rb_cCeguiTabButton,"EventClicked",wrap(CEGUI::TabButton::EventClicked));

	rb_define_const(rb_cCeguiTabButton,"EventDragged",wrap(CEGUI::TabButton::EventDragged));
	rb_define_const(rb_cCeguiTabButton,"EventScrolled",wrap(CEGUI::TabButton::EventScrolled));
}




