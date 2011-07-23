#ifndef __RubyCeguiXMLParser_H__
#define __RubyCeguiXMLParser_H__

#include "main.hpp"
void Init_CeguiXMLParser(VALUE rb_mCegui);
extern VALUE rb_cCeguiXMLParser;


#ifdef HAVE_XMLPARSERMODULES_XERCESPARSER_CEGUIXERCESPARSER_H
#include <XMLParserModules/XercesParser/CEGUIXercesParser.h>
extern VALUE rb_cCeguiXercesParser;
template <>
inline VALUE wrap< CEGUI::XercesParser >(CEGUI::XercesParser *parser )
{
	if(parser==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiXercesParser, NULL, NULL, parser);
}
#endif

#ifdef HAVE_XMLPARSERMODULES_EXPATPARSER_CEGUIEXPATPARSER_H
#include <XMLParserModules/ExpatParser/CEGUIExpatParser.h>
extern VALUE rb_cCeguiExpatParser;
template <>
inline VALUE wrap< CEGUI::ExpatParser >(CEGUI::ExpatParser *parser )
{
	if(parser==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiExpatParser, NULL, NULL, parser);
}
#endif

#ifdef HAVE_XMLPARSERMODULES_LIBXMLPARSER_CEGUILIBXMLPARSER_H
#include <XMLParserModules/LibxmlParser/CEGUILibxmlParser.h>
extern VALUE rb_cCeguiLibXMLParser;
template <>
inline VALUE wrap< CEGUI::LibxmlParser >(CEGUI::LibxmlParser *parser )
{
	if(parser==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiLibXMLParser, NULL, NULL, parser);
}
#endif
#ifdef HAVE_XMLPARSERMODULES_TINYXMLPARSER_CEGUITINYXMLPARSER_H
#include <XMLParserModules/TinyXMLParser/CEGUITinyXMLParser.h>
extern VALUE rb_cCeguiTinyXMLParser;
template <>
inline VALUE wrap< CEGUI::TinyXMLParser >(CEGUI::TinyXMLParser *parser )
{
	if(parser==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiTinyXMLParser, NULL, NULL, parser);
}
#endif


template <>
inline VALUE wrap< CEGUI::XMLParser >(CEGUI::XMLParser *parser )
{
	if(parser==NULL)
		return Qnil;
#ifdef HAVE_XMLPARSERMODULES_XERCESPARSER_CEGUIXERCESPARSER_H
	CEGUI::XercesParser *xercesparser = dynamic_cast<CEGUI::XercesParser*>(parser);
	if(xercesparser)
		return wrap(xercesparser);
#endif
#ifdef HAVE_XMLPARSERMODULES_EXPATPARSER_CEGUIEXPATPARSER_H
	CEGUI::ExpatParser *expatparser = dynamic_cast<CEGUI::ExpatParser*>(parser);
	if(expatparser)
		return wrap(expatparser);
#endif
#ifdef HAVE_XMLPARSERMODULES_LIBXMLPARSER_CEGUILIBXMLPARSER_H
	CEGUI::LibxmlParser *libxmlparser = dynamic_cast<CEGUI::LibxmlParser*>(parser);
	if(libxmlparser)
		return wrap(libxmlparser);
#endif
#ifdef HAVE_XMLPARSERMODULES_TINYXMLPARSER_CEGUITINYXMLPARSER_H
	CEGUI::TinyXMLParser *tinyxmlparser = dynamic_cast<CEGUI::TinyXMLParser*>(parser);
	if(tinyxmlparser)
		return wrap(tinyxmlparser);
#endif
	return Data_Wrap_Struct(rb_cCeguiXMLParser, NULL, NULL, parser);
}
template <>
inline CEGUI::XMLParser* wrap< CEGUI::XMLParser* >(const VALUE &vparser)
{
	if (rb_obj_is_kind_of(vparser, rb_cCeguiXMLParser)){
		CEGUI::XMLParser *parser;
		Data_Get_Struct( vparser, CEGUI::XMLParser, parser);
		return parser;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiXMLParser),rb_obj_classname(vparser));
		return NULL;
	}
}
#endif /* __RubyCeguiXMLParser_H__ */
