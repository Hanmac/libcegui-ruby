#include "ceguixmlparser.hpp"
#include "ceguipropertyset.hpp"
#include "ceguiexception.hpp"
#include "ceguixmlhandler.hpp"

#define _self wrap<CEGUI::XMLParser*>(self)

VALUE rb_cCeguiXMLParser;

namespace CeguiXMLParser {

singlereturn(getIdentifierString)
singlereturn(initialise)
singlefunc(cleanup)


/*
*/
VALUE _parseXMLFile(VALUE self,VALUE handler,VALUE filename,VALUE schemaName,VALUE resourceGroup)
{
	CEGUI::XMLHandler *temp = wrap<CEGUI::XMLHandler*>(handler);
	_self->parseXMLFile(*temp,wrap<CEGUI::String>(filename),wrap<CEGUI::String>(schemaName),wrap<CEGUI::String>(resourceGroup));
	return Qnil;
}
/*
*/
VALUE _parseXMLString(VALUE self,VALUE handler,VALUE filename,VALUE schemaName)
{
	CEGUI::XMLHandler *temp = wrap<CEGUI::XMLHandler*>(handler);
	_self->parseXMLString(*temp,wrap<CEGUI::String>(filename),wrap<CEGUI::String>(schemaName));
	return Qnil;
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
	VALUE array[2];
	array[0]=rb_str_new2("#<%s>");
	array[1]=self;
	return rb_f_sprintf(2,array);
}


}


/* Document-method: name
*/

/*
*/
void Init_CeguiXMLParser(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
#endif
	using namespace CeguiXMLParser;

	rb_cCeguiXMLParser = rb_define_class_under(rb_mCegui,"XMLParser",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiXMLParser);

	rb_include_module(rb_cCeguiXMLParser,rb_mCeguiPropertySet);

	rb_define_method(rb_cCeguiXMLParser,"name",RUBY_METHOD_FUNC(_getIdentifierString),0);
	rb_define_method(rb_cCeguiXMLParser,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	
	rb_define_alias(rb_cCeguiXMLParser,"to_s","name");

	rb_define_method(rb_cCeguiXMLParser,"initialise",RUBY_METHOD_FUNC(_initialise),0);
	rb_define_method(rb_cCeguiXMLParser,"cleanup",RUBY_METHOD_FUNC(_cleanup),0);

	rb_define_method(rb_cCeguiXMLParser,"parseXMLFile",RUBY_METHOD_FUNC(_parseXMLFile),4);
	rb_define_method(rb_cCeguiXMLParser,"parseXMLString",RUBY_METHOD_FUNC(_parseXMLString),3);
}
