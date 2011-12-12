#include "ceguimenubase.hpp"
#include "ceguiitemlistbase.hpp"

#include "ceguiwindow.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::MenuBase*>(self)
VALUE rb_cCeguiMenuBase;

namespace CeguiMenuBase {

macro_attr(ItemSpacing,float)
macro_attr(AutoCloseNestedPopups,bool)

}
void Init_CeguiMenuBase(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemListBase = rb_define_class_under(rb_mCegui,"ItemListBase",rb_cCeguiWindow);
	
	rb_define_attr(rb_cCeguiMenuBase,"itemSpacing",1,1);
	rb_define_attr(rb_cCeguiMenuBase,"autoCloseNestedPopups",1,1);
#endif
	using namespace CeguiMenuBase;

	rb_cCeguiMenuBase = rb_define_class_under(rb_mCegui,"MenuBase",rb_cCeguiItemListBase);

	rb_define_attr_method(rb_cCeguiMenuBase,"itemSpacing",_getItemSpacing,_setItemSpacing);
	rb_define_attr_method(rb_cCeguiMenuBase,"autoCloseNestedPopups",_getAutoCloseNestedPopups,_setAutoCloseNestedPopups);
//	rb_define_method(rb_cCeguiItemListBase,"addItem",RUBY_METHOD_FUNC(CeguiItemListBase_addItem),1);

	rb_define_const(rb_cCeguiMenuBase,"EventNamespace",wrap(CEGUI::MenuBase::EventNamespace));
}
