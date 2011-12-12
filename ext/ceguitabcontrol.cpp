/*
 * ceguitabcontrol.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::TabControl*>(self)
VALUE rb_cCeguiTabControl;

namespace CeguiTabControl {

macro_attr(TabHeight,CEGUI::UDim)
macro_attr(TabTextPadding,CEGUI::UDim)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::TabControl::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

}
/*
*/
void Init_CeguiTabControl(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiTabControl,"tabHeight",1,1);
	rb_define_attr(rb_cCeguiTabControl,"tabTextPadding",1,1);
#endif
	using namespace CeguiTabControl;

	rb_cCeguiTabControl = rb_define_class_under(rb_mCegui,"TabControl",rb_cCeguiWindow);

	rb_define_attr_method(rb_cCeguiTabControl,"tabHeight",_getTabHeight,_setTabHeight);
	rb_define_attr_method(rb_cCeguiTabControl,"tabTextPadding",_getTabTextPadding,_setTabTextPadding);

	rb_define_singleton_method(rb_cCeguiTabControl,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiTabControl,"WidgetTypeName",wrap(CEGUI::TabControl::WidgetTypeName));
	rb_define_const(rb_cCeguiTabControl,"EventNamespace",wrap(CEGUI::TabControl::EventNamespace));

	rb_define_const(rb_cCeguiTabControl,"EventSelectionChanged",wrap(CEGUI::TabControl::EventSelectionChanged));

	rb_define_const(rb_cCeguiTabControl,"ContentPaneName",wrap(CEGUI::TabControl::ContentPaneName));
	rb_define_const(rb_cCeguiTabControl,"TabButtonName",wrap(CEGUI::TabControl::TabButtonName));
	rb_define_const(rb_cCeguiTabControl,"TabButtonPaneName",wrap(CEGUI::TabControl::TabButtonPaneName));
	rb_define_const(rb_cCeguiTabControl,"ButtonScrollLeft",wrap(CEGUI::TabControl::ButtonScrollLeft));
	rb_define_const(rb_cCeguiTabControl,"ButtonScrollRight",wrap(CEGUI::TabControl::ButtonScrollRight));

}






