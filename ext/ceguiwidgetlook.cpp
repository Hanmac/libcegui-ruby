#include "ceguiwidgetlook.hpp"
#include "ceguiexception.hpp"


#define _self wrap<CEGUI::WidgetLookFeel*>(self)

VALUE rb_cCeguiWidgetLook;

/*
*/
VALUE CeguiWidgetLook_Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::WidgetLookManager::getDefaultResourceGroup());
}
/*
*/
VALUE CeguiWidgetLook_Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::WidgetLookManager::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}


void Init_CeguiWidgetLook(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiWidgetLook = rb_define_class_under(rb_mCegui,"WidgetLook",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiWidgetLook);

	rb_define_singleton_method(rb_cCeguiWidgetLook,"defaultResourceGroup",RUBY_METHOD_FUNC(CeguiWidgetLook_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiWidgetLook,"defaultResourceGroup=",RUBY_METHOD_FUNC(CeguiWidgetLook_Manager_setDefaultResourceGroup),1);

}
