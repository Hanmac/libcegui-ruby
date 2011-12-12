/*
 * ceguidefaultrenderedstringparser.hpp
 *
 *  Created on: 03.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiDefaultRenderedStringParser_H__
#define __RubyCeguiDefaultRenderedStringParser_H__

#include "main.hpp"
void Init_CeguiDefaultRenderedStringParser(VALUE rb_mCegui);
extern VALUE rb_cCeguiDefaultRenderedStringParser;

template <>
inline VALUE wrap< CEGUI::DefaultRenderedStringParser >(CEGUI::DefaultRenderedStringParser *parser )
{
	return Data_Wrap_Struct(rb_cCeguiDefaultRenderedStringParser, NULL, free, parser);
}

template <>
inline CEGUI::DefaultRenderedStringParser* wrap< CEGUI::DefaultRenderedStringParser* >(const VALUE &vparser)
{
	if(rb_obj_is_kind_of(vparser, rb_cCeguiDefaultRenderedStringParser)){
		CEGUI::DefaultRenderedStringParser *parser;
		Data_Get_Struct( vparser, CEGUI::DefaultRenderedStringParser, parser);
		return parser;
	}else {
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiDefaultRenderedStringParser),rb_obj_classname(vparser));
		return NULL;
	}
}

#endif /* __RubyCeguiDefaultRenderedStringParser_H__ */
