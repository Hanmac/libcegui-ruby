#include "ceguipopupmenu.hpp"
#include "ceguimenubase.hpp"
#include "ceguiitemlistbase.hpp"
#include "ceguiwindow.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::PopupMenu*>(self)
VALUE rb_cCeguiPopupMenu;

macro_attr_with_func(PopupMenu,FadeInTime,DBL2NUM,NUM2DBL)
macro_attr_with_func(PopupMenu,FadeOutTime,DBL2NUM,NUM2DBL)

/*
*/
VALUE CeguiPopupMenu_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::PopupMenu::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}


/*
*/
void Init_CeguiPopupMenu(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemListBase = rb_define_class_under(rb_mCegui,"ItemListBase",rb_cCeguiWindow);
	rb_cCeguiMenuBase = rb_define_class_under(rb_mCegui,"MenuBase",rb_cCeguiItemListBase);
	
	rb_define_attr(rb_cCeguiPopupMenu,"fadeInTime",1,1);
	rb_define_attr(rb_cCeguiPopupMenu,"fadeOutTime",1,1);
#endif

	rb_cCeguiPopupMenu = rb_define_class_under(rb_mCegui,"PopupMenu",rb_cCeguiMenuBase);

	rb_define_attr_method(rb_cCeguiPopupMenu,"fadeInTime",CeguiPopupMenu_getFadeInTime,CeguiPopupMenu_setFadeInTime);
	rb_define_attr_method(rb_cCeguiPopupMenu,"fadeOutTime",CeguiPopupMenu_getFadeOutTime,CeguiPopupMenu_setFadeOutTime);

	rb_define_singleton_method(rb_cCeguiPopupMenu,"new",RUBY_METHOD_FUNC(CeguiPopupMenu_new),-1);
	
	rb_define_const(rb_cCeguiPopupMenu,"WidgetTypeName",wrap(CEGUI::PopupMenu::WidgetTypeName));
	rb_define_const(rb_cCeguiPopupMenu,"EventNamespace",wrap(CEGUI::PopupMenu::EventNamespace));
}
