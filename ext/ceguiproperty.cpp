#include "ceguiproperty.hpp"
#include "ceguipropertyset.hpp"
#include "ceguixmlserializer.hpp"
#define _self wrap<CEGUI::Property*>(self)
VALUE rb_cCeguiProperty;
namespace CeguiProperty {

singlereturn(getName)
singlereturn(getHelp)
singlereturn(getDataType)
singlereturn(getOrigin)


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
	array[2]=_getName(self);
	return rb_f_sprintf(3,array);
}


/*
*/
VALUE _get(VALUE self,VALUE set)
{
	return wrap(_self->get(wrap<CEGUI::PropertySet*>(set)));
}


/*
*/
VALUE _set(VALUE self,VALUE set,VALUE value)
{
	_self->set(wrap<CEGUI::PropertySet*>(set),wrap<CEGUI::String>(value));
	return self;
}

/*
*/
VALUE _writeXML(VALUE self,VALUE set,VALUE xml)
{
	CEGUI::XMLSerializer *temp =wrap<CEGUI::XMLSerializer*>(xml);
	_self->writeXMLToStream(wrap<CEGUI::PropertySet*>(set),*temp);
	return self;
}

}


void Init_CeguiProperty(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif
	using namespace CeguiProperty;
	rb_cCeguiProperty = rb_define_class_under(rb_mCegui,"Property",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiProperty);
	
	rb_define_method(rb_cCeguiProperty,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiProperty,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cCeguiProperty,"help",RUBY_METHOD_FUNC(_getHelp),0);
	rb_define_method(rb_cCeguiProperty,"dataType",RUBY_METHOD_FUNC(_getDataType),0);
	rb_define_method(rb_cCeguiProperty,"origin",RUBY_METHOD_FUNC(_getOrigin),0);

	rb_define_method(rb_cCeguiProperty,"get",RUBY_METHOD_FUNC(_get),1);
	rb_define_method(rb_cCeguiProperty,"set",RUBY_METHOD_FUNC(_set),2);
	
	rb_define_method(rb_cCeguiProperty,"writeXML",RUBY_METHOD_FUNC(_writeXML),2);
}
