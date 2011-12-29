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
	return unwrapPtr<CEGUI::BasicRenderedStringParser>(vparser, rb_cCeguiBasicRenderedStringParser);
}

#endif /* __RubyCeguiBasicRenderedStringParser_H__ */
