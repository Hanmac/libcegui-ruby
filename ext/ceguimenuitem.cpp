#include "ceguimenuitem.hpp"

#include "ceguiwindow.hpp"

#include "ceguiuvector2.hpp"

#define _self wrap<CEGUI::MenuItem*>(self)
VALUE rb_cCeguiMenuItem;

namespace CeguiMenuItem {

macro_attr(PopupMenu,CEGUI::PopupMenu*)
macro_attr(PopupOffset,CEGUI::UVector2)

macro_attr(AutoPopupTimeout,float)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::MenuItem::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

}
/*
*/
void Init_CeguiMenuItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemEntry = rb_define_class_under(rb_mCegui,"ItemEntry",rb_cCeguiWindow);
	
	rb_define_attr(rb_cCeguiMenuItem,"popupMenu",1,1);
	rb_define_attr(rb_cCeguiMenuItem,"popupOffset",1,1);
	rb_define_attr(rb_cCeguiMenuItem,"autoPopupTimeout",1,1);
#endif
	using namespace CeguiMenuItem;

	rb_cCeguiMenuItem = rb_define_class_under(rb_mCegui,"MenuItem",rb_cCeguiItemEntry);

	rb_define_attr_method(rb_cCeguiMenuItem,"popupMenu",_getPopupMenu,_setPopupMenu);
	rb_define_attr_method(rb_cCeguiMenuItem,"popupOffset",_getPopupOffset,_setPopupOffset);
	rb_define_attr_method(rb_cCeguiMenuItem,"autoPopupTimeout",_getAutoPopupTimeout,_setAutoPopupTimeout);


	rb_define_singleton_method(rb_cCeguiMenuItem,"new",RUBY_METHOD_FUNC(_new),-1);
	
	rb_define_const(rb_cCeguiMenuItem,"WidgetTypeName",wrap(CEGUI::MenuItem::WidgetTypeName));	
	rb_define_const(rb_cCeguiMenuItem,"EventNamespace",wrap(CEGUI::MenuItem::EventNamespace));

}
