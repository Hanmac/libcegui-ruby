#include "ceguiwidgetlook.hpp"
#include "ceguiexception.hpp"


#define _self wrap<CEGUI::WidgetLookFeel*>(self)
#define _manager CEGUI::WidgetLookManager::getSingletonPtr()

VALUE rb_cCeguiWidgetLook;
namespace CeguiWidgetLook {
VALUE _manager_get(VALUE self,VALUE name)
{
	if(_manager->isWidgetLookAvailable(wrap<CEGUI::String>(name)))
		return wrap(_manager->getWidgetLook(wrap<CEGUI::String>(name)));
	return Qnil;
}

/*
*/
VALUE _manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::WidgetLookManager::getDefaultResourceGroup());
}
/*
*/
VALUE _manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::WidgetLookManager::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}

}

void Init_CeguiWidgetLook(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
#endif
	using namespace CeguiWidgetLook;

	rb_cCeguiWidgetLook = rb_define_class_under(rb_mCegui,"WidgetLook",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiWidgetLook);


	rb_define_singleton_method(rb_cCeguiWidgetLook,"defaultResourceGroup",RUBY_METHOD_FUNC(_manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiWidgetLook,"defaultResourceGroup=",RUBY_METHOD_FUNC(_manager_setDefaultResourceGroup),1);

	rb_define_singleton_method(rb_cCeguiWidgetLook,"[]",RUBY_METHOD_FUNC(_manager_get),1);
}
