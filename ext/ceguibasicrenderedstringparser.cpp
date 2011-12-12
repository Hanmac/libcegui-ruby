/*
 * ceguibasicrenderedstringparser.cpp
 *
 *  Created on: 03.12.2011
 *      Author: hanmac
 */

#include "ceguirenderedstringparser.hpp"

#define _self wrap<CEGUI::BasicRenderedStringParser*>(self)
VALUE rb_cCeguiBasicRenderedStringParser;

namespace BasicRenderedStringParser {
/*
*/
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::DefaultRenderedStringParser);
}
/*
 *
 */
VALUE _parse(VALUE self,VALUE input_string,VALUE initial_font,VALUE initial_colours)
{
	return wrap(_self->parse(wrap<CEGUI::String>(input_string),
			wrap<CEGUI::Font*>(initial_font),
			wrap<CEGUI::ColourRect*>(initial_colours)));
}

}
/*
*/
void Init_CeguiBasicRenderedStringParser(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_mCeguiRenderedStringParser = rb_define_module_under(rb_mCegui,"RenderedStringParser");

#endif
	using namespace BasicRenderedStringParser;

	rb_cCeguiBasicRenderedStringParser = rb_define_class_under(rb_mCegui,"BasicRenderedStringParser",rb_cObject);
	rb_include_module(rb_cCeguiBasicRenderedStringParser,rb_mCeguiRenderedStringParser);
	rb_define_alloc_func(rb_cCeguiBasicRenderedStringParser,_alloc);

	rb_define_method(rb_cCeguiBasicRenderedStringParser,"parse",RUBY_METHOD_FUNC(_parse),3);

}


