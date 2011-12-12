#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::DefaultWindow*>(self)
VALUE rb_cCeguiDefaultWindow;

/*
*/
VALUE CeguiDefaultWindow_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::DefaultWindow::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
void Init_CeguiDefaultWindow(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

#endif

	rb_cCeguiDefaultWindow = rb_define_class_under(rb_mCegui,"DefaultWindow",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiDefaultWindow,"new",RUBY_METHOD_FUNC(CeguiDefaultWindow_new),-1);

	rb_define_const(rb_cCeguiDefaultWindow,"WidgetTypeName",wrap(CEGUI::DefaultWindow::WidgetTypeName));	


}
