/*
 * ceguitextcomponent.cpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */

#include "ceguicomponentbase.hpp"
#include "ceguiexception.hpp"

#include "ceguiimage.hpp"

#define _self wrap<CEGUI::TextComponent*>(self)
VALUE rb_cCeguiTextComponent;

namespace CeguiTextComponent
{
/*
 *
 */
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::TextComponent);
}

macro_attr(Text,CEGUI::String)
macro_attr(Font,CEGUI::String)


macro_attr(TextPropertySource,CEGUI::String)
macro_attr(FontPropertySource,CEGUI::String)

macro_attr(VerticalFormatting,CEGUI::VerticalTextFormatting)
macro_attr(HorizontalFormatting,CEGUI::HorizontalTextFormatting)

}
/*
 *
*/

void Init_CeguiTextComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiTextComponent,"text",1,1);
	rb_define_attr(rb_cCeguiTextComponent,"font",1,1);

	rb_define_attr(rb_cCeguiTextComponent,"textPropertySource",1,1);
	rb_define_attr(rb_cCeguiTextComponent,"fontPropertySource",1,1);

	rb_define_attr(rb_cCeguiTextComponent,"verticalFormatting",1,1);
	rb_define_attr(rb_cCeguiTextComponent,"horizontalFormatting",1,1);
	rb_cCeguiComponentBase = rb_define_class_under(rb_mCegui,"ComponentBase",rb_cObject);

#endif

	using namespace CeguiTextComponent;
	rb_cCeguiTextComponent = rb_define_class_under(rb_mCegui,"TextComponent",rb_cCeguiComponentBase);
	rb_define_alloc_func(rb_cCeguiTextComponent,_alloc);

	rb_include_module(rb_cCeguiTextComponent,rb_mEnumerable);

	rb_define_attr_method(rb_cCeguiTextComponent,"text",_getText,_setText);
	rb_define_attr_method(rb_cCeguiTextComponent,"font",_getFont,_setFont);

	rb_define_attr_method(rb_cCeguiTextComponent,"textPropertySource",_getTextPropertySource,_setTextPropertySource);
	rb_define_attr_method(rb_cCeguiTextComponent,"fontPropertySource",_getFontPropertySource,_setFontPropertySource);


	rb_define_attr_method(rb_cCeguiTextComponent,"verticalFormatting",_getVerticalFormatting,_setVerticalFormatting);
	rb_define_attr_method(rb_cCeguiTextComponent,"horizontalFormatting",_getHorizontalFormatting,_setHorizontalFormatting);


}



