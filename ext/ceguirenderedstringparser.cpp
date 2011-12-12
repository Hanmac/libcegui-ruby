/*
 * ceguirenderedstringparser.cpp
 *
 *  Created on: 03.12.2011
 *      Author: hanmac
 */

#include "ceguirenderedstringparser.hpp"

VALUE rb_mCeguiRenderedStringParser;
std::map<VALUE, RubyRenderedStringParser*> renderedparserholder;

/* Document-method: parse
*/
/*
*/
void Init_CeguiRenderedStringParser(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif
	rb_mCeguiRenderedStringParser = rb_define_module_under(rb_mCegui,"RenderedStringParser");
	rb_define_method(rb_mCeguiRenderedStringParser,"parse",RUBY_METHOD_FUNC(Cegui_dummy3),3);

}

