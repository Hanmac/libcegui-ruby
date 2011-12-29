/*
 * ceguiwidgetcomponent.cpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */

#include "ceguiwidgetcomponent.hpp"
#include "ceguicomponentarea.hpp"
#include "ceguipropertyinitialiser.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::WidgetComponent*>(self)

VALUE rb_cCeguiWidgetComponent;
namespace CeguiWidgetComponent {

macro_attr(ComponentArea,CEGUI::ComponentArea)

macro_attr(BaseWidgetType,CEGUI::String)
macro_attr(WidgetLookName,CEGUI::String)
macro_attr(WidgetName,CEGUI::String)
macro_attr(WindowRendererType,CEGUI::String)

macro_attr(VerticalWidgetAlignment,CEGUI::VerticalAlignment)
macro_attr(HorizontalWidgetAlignment,CEGUI::HorizontalAlignment)



VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::WidgetComponent);
}

/*
 * call-seq:
 *   inspect -> String
 *
 * Human-readable description.
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(self,"name");
	return rb_f_sprintf(3,array);
}
/*
 *
 */
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getPropertyIterator());
	return self;
}

VALUE _get(VALUE self,VALUE name)
{
	return wrap(_self->findPropertyInitialiser(wrap<CEGUI::String>(name)));
}

}

void Init_CeguiWidgetComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiWidgetComponent,"componentArea",1,1);

	rb_define_attr(rb_cCeguiWidgetComponent,"baseWidgetType",1,1);
	rb_define_attr(rb_cCeguiWidgetComponent,"widgetLookName",1,1);
	rb_define_attr(rb_cCeguiWidgetComponent,"widgetName",1,1);
	rb_define_attr(rb_cCeguiWidgetComponent,"windowRendererType",1,1);

	rb_define_attr(rb_cCeguiWidgetComponent,"verticalWidgetAlignment",1,1);
	rb_define_attr(rb_cCeguiWidgetComponent,"horizontalWidgetAlignment",1,1);
#endif
	using namespace CeguiWidgetComponent;

	rb_cCeguiWidgetComponent = rb_define_class_under(rb_mCegui,"WidgetComponent",rb_cObject);

	rb_define_alloc_func(rb_cCeguiWidgetComponent,_alloc);

	rb_define_attr_method(rb_cCeguiWidgetComponent,"componentArea",_getComponentArea,_setComponentArea);

	rb_define_attr_method(rb_cCeguiWidgetComponent,"baseWidgetType",_getBaseWidgetType,_setBaseWidgetType);
	rb_define_attr_method(rb_cCeguiWidgetComponent,"widgetLookName",_getWidgetLookName,_setWidgetLookName);
	rb_define_attr_method(rb_cCeguiWidgetComponent,"widgetName",_getWidgetName,_setWidgetName);
	rb_define_attr_method(rb_cCeguiWidgetComponent,"windowRendererType",_getWindowRendererType,_setWindowRendererType);

	rb_define_attr_method(rb_cCeguiWidgetComponent,"verticalWidgetAlignment",_getVerticalWidgetAlignment,_setVerticalWidgetAlignment);
	rb_define_attr_method(rb_cCeguiWidgetComponent,"horizontalWidgetAlignment",_getHorizontalWidgetAlignment,_setHorizontalWidgetAlignment);

	rb_define_method(rb_cCeguiWidgetComponent,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiWidgetComponent,"[]",RUBY_METHOD_FUNC(_get),1);
	rb_define_method(rb_cCeguiWidgetComponent,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cCeguiWidgetComponent,rb_mEnumerable);
}





