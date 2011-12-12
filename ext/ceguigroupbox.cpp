/*
 * ceguigroupbox.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::GroupBox*>(self)
VALUE rb_cCeguiGroupBox;

/*
*/
VALUE CeguiGroupBox_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::GroupBox::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
void Init_CeguiGroupBox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

#endif

	rb_cCeguiGroupBox = rb_define_class_under(rb_mCegui,"GroupBox",rb_cCeguiWindow);

	rb_define_singleton_method(rb_cCeguiGroupBox,"new",RUBY_METHOD_FUNC(CeguiGroupBox_new),-1);

	rb_define_const(rb_cCeguiGroupBox,"EventNamespace",wrap(CEGUI::GroupBox::EventNamespace));
	rb_define_const(rb_cCeguiGroupBox,"WidgetTypeName",wrap(CEGUI::GroupBox::WidgetTypeName));
}




