#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::LayoutContainer*>(self)
VALUE rb_cCeguiLayoutContainer;

/*
*/
void Init_CeguiLayoutContainer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemListBase = rb_define_class_under(rb_mCegui,"ItemListBase",rb_cCeguiWindow);
	rb_cCeguiMenuBase = rb_define_class_under(rb_mCegui,"MenuBase",rb_cCeguiItemListBase);
	
#endif

	rb_cCeguiLayoutContainer = rb_define_class_under(rb_mCegui,"LayoutContainer",rb_cCeguiWindow);

	
	rb_define_const(rb_cCeguiLayoutContainer,"EventNamespace",wrap(CEGUI::LayoutContainer::EventNamespace));
}
