#include "ceguimenubase.hpp"
#include "ceguiitemlistbase.hpp"

#include "ceguiwindow.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::MenuBase*>(self)
VALUE rb_cCeguiMenuBase;

macro_attr_with_func(MenuBase,ItemSpacing,DBL2NUM,NUM2DBL)
macro_attr_with_func(MenuBase,AutoCloseNestedPopups,RBOOL,RTEST)

void Init_CeguiMenuBase(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemListBase = rb_define_class_under(rb_mCegui,"ItemListBase",rb_cCeguiWindow);
	
	rb_define_attr(rb_cCeguiMenuBase,"itemSpacing",1,1);
	rb_define_attr(rb_cCeguiMenuBase,"autoCloseNestedPopups",1,1);
#endif

	rb_cCeguiMenuBase = rb_define_class_under(rb_mCegui,"MenuBase",rb_cCeguiItemListBase);

	rb_define_attr_method(rb_cCeguiMenuBase,"itemSpacing",CeguiMenuBase_getItemSpacing,CeguiMenuBase_setItemSpacing);
	rb_define_attr_method(rb_cCeguiMenuBase,"autoCloseNestedPopups",CeguiMenuBase_getAutoCloseNestedPopups,CeguiMenuBase_setAutoCloseNestedPopups);
//	rb_define_method(rb_cCeguiItemListBase,"addItem",RUBY_METHOD_FUNC(CeguiItemListBase_addItem),1);

	rb_define_const(rb_cCeguiMenuBase,"EventNamespace",wrap(CEGUI::MenuBase::EventNamespace));	
}
