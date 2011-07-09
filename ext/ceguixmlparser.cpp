#include "ceguixmlparser.hpp"
#include "ceguipropertyset.hpp"
#include "ceguiexception.hpp"


#define _self wrap<CEGUI::XMLParser*>(self)

VALUE rb_cCeguiXMLParser;

/*
*/
VALUE CeguiXMLParser_getName(VALUE self)
{
	return wrap(_self->getIdentifierString());
}

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiXMLParser_inspect(VALUE self)
{
	VALUE array[2];
	array[0]=rb_str_new2("#<%s>");
	array[1]=CeguiXMLParser_getName(self);
	return rb_f_sprintf(2,array);
}




void Init_CeguiXMLParser(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiXMLParser = rb_define_class_under(rb_mCegui,"XMLParser",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiXMLParser);

	rb_include_module(rb_cCeguiXMLParser,rb_mCeguiPropertySet);

	rb_define_method(rb_cCeguiXMLParser,"name",RUBY_METHOD_FUNC(CeguiXMLParser_getName),0);
	rb_define_method(rb_cCeguiXMLParser,"inspect",RUBY_METHOD_FUNC(CeguiXMLParser_inspect),0);

}
