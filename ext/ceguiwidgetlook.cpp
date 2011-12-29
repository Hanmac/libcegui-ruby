#include "ceguiwidgetlook.hpp"

#include "ceguiwidgetcomponent.hpp"
#include "ceguiimagerysection.hpp"
#include "ceguistateimagery.hpp"
#include "ceguinamedarea.hpp"
#include "ceguipropertyinitialiser.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::WidgetLookFeel*>(self)
#define _manager CEGUI::WidgetLookManager::getSingletonPtr()

VALUE rb_cCeguiWidgetLook;
namespace CeguiWidgetLook {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::WidgetLookFeel);
}

/*
 *
 */
VALUE _each_State(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getStateIterator());
	return self;
}

/*
 *
 */
VALUE _each_Imagery(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getImageryIterator());
	return self;
}
/*
 *
 */
VALUE _each_NamedArea(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getNamedAreaIterator());
	return self;
}
/*
 *
 */
VALUE _each_WidgetComponent(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getWidgetComponentIterator());
	return self;
}
/*
 *
 */
VALUE _each_PropertyInitialiser(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getPropertyInitialiserIterator());
	return self;
}



/*
 *
 */
VALUE _getState(VALUE self,VALUE name)
{
	if(_self->isStateImageryPresent(wrap<CEGUI::String>(name)))
		return wrap(_self->getStateImagery(wrap<CEGUI::String>(name)));
	else
		return Qnil;
}

/*
 *
 */
VALUE _getImagery(VALUE self,VALUE name)
{
//	if(_self->isImagerySectionDefined(wrap<CEGUI::String>(name)))
		return wrap(_self->getImagerySection(wrap<CEGUI::String>(name)));
//	else
		return Qnil;
}

/*
 *
 */
VALUE _getNamedArea(VALUE self,VALUE name)
{
	if(_self->isNamedAreaDefined(wrap<CEGUI::String>(name)))
		return wrap(_self->getNamedArea(wrap<CEGUI::String>(name)));
	else
		return Qnil;
}
/*
 *
 */
VALUE _getWidgetComponent(VALUE self,VALUE name)
{
	return wrap(_self->findWidgetComponent(wrap<CEGUI::String>(name)));
}

/*
 *
 */
VALUE _getPropertyInitialiser(VALUE self,VALUE name)
{
	return wrap(_self->findPropertyInitialiser(wrap<CEGUI::String>(name)));
}



/*
 *
 */
VALUE _manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_manager->getWidgetLookIterator());
	return self;
}

/*
 *
 */
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
	rb_define_alloc_func(rb_cCeguiWidgetLook,_alloc);

	rb_define_method(rb_cCeguiWidgetLook,"each_State",RUBY_METHOD_FUNC(_each_State),0);
	rb_define_method(rb_cCeguiWidgetLook,"each_Imagery",RUBY_METHOD_FUNC(_each_Imagery),0);
	rb_define_method(rb_cCeguiWidgetLook,"each_NamedArea",RUBY_METHOD_FUNC(_each_NamedArea),0);
	rb_define_method(rb_cCeguiWidgetLook,"each_WidgetComponent",RUBY_METHOD_FUNC(_each_WidgetComponent),0);
	rb_define_method(rb_cCeguiWidgetLook,"each_PropertyInitialiser",RUBY_METHOD_FUNC(_each_PropertyInitialiser),0);

	rb_define_method(rb_cCeguiWidgetLook,"getState",RUBY_METHOD_FUNC(_getState),1);
	rb_define_method(rb_cCeguiWidgetLook,"getImagery",RUBY_METHOD_FUNC(_getImagery),1);
	rb_define_method(rb_cCeguiWidgetLook,"getNamedArea",RUBY_METHOD_FUNC(_getNamedArea),1);
	rb_define_method(rb_cCeguiWidgetLook,"getWidgetComponent",RUBY_METHOD_FUNC(_getWidgetComponent),1);
	rb_define_method(rb_cCeguiWidgetLook,"getPropertyInitialiser",RUBY_METHOD_FUNC(_getPropertyInitialiser),1);


	rb_define_singleton_method(rb_cCeguiWidgetLook,"defaultResourceGroup",RUBY_METHOD_FUNC(_manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiWidgetLook,"defaultResourceGroup=",RUBY_METHOD_FUNC(_manager_setDefaultResourceGroup),1);

	rb_define_singleton_method(rb_cCeguiWidgetLook,"[]",RUBY_METHOD_FUNC(_manager_get),1);
	rb_define_singleton_method(rb_cCeguiWidgetLook,"each",RUBY_METHOD_FUNC(_manager_each),0);
	rb_extend_object(rb_cCeguiWidgetLook,rb_mEnumerable);
}
