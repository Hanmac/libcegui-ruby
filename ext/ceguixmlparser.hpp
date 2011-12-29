#ifndef __RubyCeguiXMLParser_H__
#define __RubyCeguiXMLParser_H__

#include "main.hpp"
void Init_CeguiXMLParser(VALUE rb_mCegui);
extern VALUE rb_cCeguiXMLParser;

template <>
inline VALUE wrap< CEGUI::XMLParser >(CEGUI::XMLParser *parser )
{
	if(parser==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiXMLParser, NULL, NULL, parser);
}
template <>
inline CEGUI::XMLParser* wrap< CEGUI::XMLParser* >(const VALUE &vparser)
{
	return unwrapPtr<CEGUI::XMLParser>(vparser, rb_cCeguiXMLParser);
}
#endif /* __RubyCeguiXMLParser_H__ */
