#include "ceguixmlparser.hpp"
#include "ceguipropertyset.hpp"
#include "ceguiexception.hpp"
#include "ceguixmlhandler.hpp"

#define _self wrap<CEGUI::XMLParser*>(self)

VALUE rb_cCeguiXMLParser;

#ifdef HAVE_XMLPARSERMODULES_XERCESPARSER_CEGUIXERCESPARSER_H
VALUE rb_cCeguiXercesParser;
VALUE CeguiXercesParser_alloc(VALUE self)
{
	return wrap(new CEGUI::XercesParser);
}
#endif
#ifdef HAVE_XMLPARSERMODULES_EXPATPARSER_CEGUIEXPATPARSER_H
VALUE rb_cCeguiExpatParser;
VALUE CeguiExpatParser_alloc(VALUE self)
{
	return wrap(new CEGUI::ExpatParser);
}
#endif
#ifdef HAVE_XMLPARSERMODULES_LIBXMLPARSER_CEGUILIBXMLPARSER_H
VALUE rb_cCeguiLibXMLParser;
VALUE CeguiLibXMLParser_alloc(VALUE self)
{
	return wrap(new CEGUI::LibxmlParser);
}
#endif
#ifdef HAVE_XMLPARSERMODULES_TINYXMLPARSER_CEGUITINYXMLPARSER_H
VALUE rb_cCeguiTinyXMLParser;
VALUE CeguiTinyXMLParser_alloc(VALUE self)
{
	return wrap(new CEGUI::TinyXMLParser);
}
#endif

/*
*/
VALUE CeguiXMLParser_getName(VALUE self)
{
	return wrap(_self->getIdentifierString());
}


/*
*/
VALUE CeguiXMLParser_initialise(VALUE self)
{
	return RBOOL(_self->initialise());
}
/*
*/
VALUE CeguiXMLParser_cleanup(VALUE self)
{
	_self->cleanup();
	return Qnil;
}

/*
*/
VALUE CeguiXMLParser_parseXMLFile(VALUE self,VALUE handler,VALUE filename,VALUE schemaName,VALUE resourceGroup)
{
	CEGUI::XMLHandler *temp = wrap<CEGUI::XMLHandler*>(handler);
	_self->parseXMLFile(*temp,wrap<CEGUI::String>(filename),wrap<CEGUI::String>(schemaName),wrap<CEGUI::String>(resourceGroup));
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
VALUE CeguiXMLParser_inspect(VALUE self)
{
	VALUE array[2];
	array[0]=rb_str_new2("#<%s>");
	array[1]=CeguiXMLParser_getName(self);
	return rb_f_sprintf(2,array);
}


/*
*/
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
	
	rb_define_method(rb_cCeguiXMLParser,"initialise",RUBY_METHOD_FUNC(CeguiXMLParser_initialise),0);
	rb_define_method(rb_cCeguiXMLParser,"cleanup",RUBY_METHOD_FUNC(CeguiXMLParser_cleanup),0);

	rb_define_method(rb_cCeguiXMLParser,"parseXMLFile",RUBY_METHOD_FUNC(CeguiXMLParser_parseXMLFile),4);
	
#ifdef HAVE_XMLPARSERMODULES_XERCESPARSER_CEGUIXERCESPARSER_H
	rb_cCeguiXercesParser = rb_define_class_under(rb_mCegui,"XercesParser",rb_cCeguiXMLParser);
	rb_define_alloc_func(rb_cCeguiXercesParser,CeguiXercesParser_alloc);
#endif
#ifdef HAVE_XMLPARSERMODULES_EXPATPARSER_CEGUIEXPATPARSER_H
	rb_cCeguiExpatParser = rb_define_class_under(rb_mCegui,"ExpatParser",rb_cCeguiXMLParser);
	rb_define_alloc_func(rb_cCeguiExpatParser,CeguiExpatParser_alloc);
#endif
#ifdef HAVE_XMLPARSERMODULES_LIBXMLPARSER_CEGUILIBXMLPARSER_H
	rb_cCeguiLibXMLParser = rb_define_class_under(rb_mCegui,"LibXMLParser",rb_cCeguiXMLParser);
	rb_define_alloc_func(rb_cCeguiLibXMLParser,CeguiLibXMLParser_alloc);
#endif
#ifdef HAVE_XMLPARSERMODULES_TINYXMLPARSER_CEGUITINYXMLPARSER_H
	rb_cCeguiTinyXMLParser = rb_define_class_under(rb_mCegui,"TinyXMLParser",rb_cCeguiXMLParser);
	rb_define_alloc_func(rb_cCeguiTinyXMLParser,CeguiTinyXMLParser_alloc);
#endif

}
