#include "ceguimenubar.hpp"
#include "ceguimenubase.hpp"
#include "ceguiitemlistbase.hpp"
#include "ceguiwindow.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Menubar*>(self)
VALUE rb_cCeguiMenubar;

/*
*/
VALUE CeguiMenubar_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Menubar::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}


/*
*/
void Init_CeguiMenubar(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemListBase = rb_define_class_under(rb_mCegui,"ItemListBase",rb_cCeguiWindow);
	rb_cCeguiMenuBase = rb_define_class_under(rb_mCegui,"MenuBase",rb_cCeguiItemListBase);
	
#endif

	rb_cCeguiMenubar = rb_define_class_under(rb_mCegui,"Menubar",rb_cCeguiMenuBase);

	rb_define_singleton_method(rb_cCeguiMenubar,"new",RUBY_METHOD_FUNC(CeguiMenubar_new),-1);
	
	rb_define_const(rb_cCeguiMenubar,"WidgetTypeName",wrap(CEGUI::Menubar::WidgetTypeName));
	rb_define_const(rb_cCeguiMenubar,"EventNamespace",wrap(CEGUI::Menubar::EventNamespace));
}
