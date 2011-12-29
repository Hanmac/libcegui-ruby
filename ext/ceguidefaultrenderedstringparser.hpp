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
	return unwrapPtr<CEGUI::DefaultRenderedStringParser>(vparser, rb_cCeguiDefaultRenderedStringParser);
}

#endif /* __RubyCeguiDefaultRenderedStringParser_H__ */
