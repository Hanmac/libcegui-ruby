#include "ceguimenuitem.hpp"

#include "ceguiwindow.hpp"

#include "ceguiuvector2.hpp"

#define _self wrap<CEGUI::MenuItem*>(self)
VALUE rb_cCeguiMenuItem;

macro_attr(MenuItem,PopupMenu,CEGUI::PopupMenu*)
macro_attr(MenuItem,PopupOffset,CEGUI::UVector2)

macro_attr_with_func(MenuItem,AutoPopupTimeout,DBL2NUM,NUM2DBL)
/*
*/
VALUE CeguiMenuItem_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::MenuItem::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
void Init_CeguiMenuItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemEntry = rb_define_class_under(rb_mCegui,"ItemEntry",rb_cCeguiWindow);
	
	rb_define_attr(rb_cCeguiMenuItem,"popupMenu",1,1);
	rb_define_attr(rb_cCeguiMenuItem,"popupOffset",1,1);
	rb_define_attr(rb_cCeguiMenuItem,"autoPopupTimeout",1,1);
#endif

	rb_cCeguiMenuItem = rb_define_class_under(rb_mCegui,"MenuItem",rb_cCeguiItemEntry);

	rb_define_attr_method(rb_cCeguiMenuItem,"popupMenu",CeguiMenuItem_getPopupMenu,CeguiMenuItem_setPopupMenu);
	rb_define_attr_method(rb_cCeguiMenuItem,"popupOffset",CeguiMenuItem_getPopupOffset,CeguiMenuItem_setPopupOffset);
	rb_define_attr_method(rb_cCeguiMenuItem,"autoPopupTimeout",CeguiMenuItem_getAutoPopupTimeout,CeguiMenuItem_setAutoPopupTimeout);


	rb_define_singleton_method(rb_cCeguiMenuItem,"new",RUBY_METHOD_FUNC(CeguiMenuItem_new),-1);
	
	rb_define_const(rb_cCeguiMenuItem,"WidgetTypeName",wrap(CEGUI::MenuItem::WidgetTypeName));	
	rb_define_const(rb_cCeguiMenuItem,"EventNamespace",wrap(CEGUI::MenuItem::EventNamespace));

}
