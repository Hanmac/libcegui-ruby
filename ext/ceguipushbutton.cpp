#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::PushButton*>(self)
VALUE rb_cCeguiPushButton;


/*
*/
VALUE CeguiPushButton_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	if(argc==2)
		return rb_call_super(2,argv);
	else{
		rb_scan_args(argc, argv, "01",&name);
		VALUE result[2];
		result[0]=wrap(CEGUI::String(CEGUI::PushButton::WidgetTypeName));
		result[1]=name;
		return rb_call_super(2,result);
	}
}


/*
*/
void Init_CeguiPushButton(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiButtonBase = rb_define_class_under(rb_mCegui,"ButtonBase",rb_cCeguiButtonBase);
#endif

	rb_cCeguiPushButton = rb_define_class_under(rb_mCegui,"PushButton",rb_cCeguiButtonBase);

	rb_define_singleton_method(rb_cCeguiPushButton,"new",RUBY_METHOD_FUNC(CeguiPushButton_new),-1);

	rb_define_const(rb_cCeguiPushButton,"WidgetTypeName",wrap(CEGUI::PushButton::WidgetTypeName));	
	rb_define_const(rb_cCeguiPushButton,"EventNamespace",wrap(CEGUI::PushButton::EventNamespace));

	rb_define_const(rb_cCeguiPushButton,"EventClicked",wrap(CEGUI::PushButton::EventClicked));
}
