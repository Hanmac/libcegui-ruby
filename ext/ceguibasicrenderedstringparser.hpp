/*
 * ceguibasicrenderedstringparser.hpp
 *
 *  Created on: 03.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiBasicRenderedStringParser_H__
#define __RubyCeguiBasicRenderedStringParser_H__

#include "main.hpp"
void Init_CeguiBasicRenderedStringParser(VALUE rb_mCegui);
extern VALUE rb_cCeguiBasicRenderedStringParser;


template <>
inline VALUE wrap< CEGUI::BasicRenderedStringParser >(CEGUI::BasicRenderedStringParser *parser )
{
	return Data_Wrap_Struct(rb_cCeguiBasicRenderedStringParser, NULL, free, parser);
}

template <>
inline CEGUI::BasicRenderedStringParser* wrap< CEGUI::BasicRenderedStringParser* >(const VALUE &vparser)
{
	if(rb_obj_is_kind_of(vparser, rb_cCeguiBasicRenderedStringParser)){
		CEGUI::BasicRenderedStringParser *parser;
		Data_Get_Struct( vparser, CEGUI::BasicRenderedStringParser, parser);
		return parser;
	}else {
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiBasicRenderedStringParser),rb_obj_classname(vparser));
		return NULL;
	}
}

#endif /* __RubyCeguiBasicRenderedStringParser_H__ */
