/*
 * ceguidefaultrenderedstringparser.cpp
 *
 *  Created on: 03.12.2011
 *      Author: hanmac
 */

#include "ceguirenderedstringparser.hpp"

#define _self wrap<CEGUI::DefaultRenderedStringParser*>(self)
VALUE rb_cCeguiDefaultRenderedStringParser;

namespace DefaultRenderedStringParser {
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
void Init_CeguiDefaultRenderedStringParser(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_mCeguiRenderedStringParser = rb_define_module_under(rb_mCegui,"RenderedStringParser");

#endif
	using namespace DefaultRenderedStringParser;

	rb_cCeguiDefaultRenderedStringParser = rb_define_class_under(rb_mCegui,"DefaultRenderedStringParser",rb_cObject);
	rb_include_module(rb_cCeguiDefaultRenderedStringParser,rb_mCeguiRenderedStringParser);
	rb_define_alloc_func(rb_cCeguiDefaultRenderedStringParser,_alloc);

	rb_define_method(rb_cCeguiDefaultRenderedStringParser,"parse",RUBY_METHOD_FUNC(_parse),3);

}


