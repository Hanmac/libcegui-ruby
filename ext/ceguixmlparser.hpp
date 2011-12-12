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
	if (rb_obj_is_kind_of(vparser, rb_cCeguiXMLParser)){
		CEGUI::XMLParser *parser;
		Data_Get_Struct( vparser, CEGUI::XMLParser, parser);
		return parser;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiXMLParser),rb_obj_classname(vparser));
		return NULL;
	}
}
#endif /* __RubyCeguiXMLParser_H__ */
