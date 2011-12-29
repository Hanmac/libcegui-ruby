/*
 * ceguiimagerycomponent.cpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */

#include "ceguicomponentbase.hpp"
#include "ceguifalagardenums.hpp"
#include "ceguiexception.hpp"

#include "ceguiimage.hpp"

#define _self wrap<CEGUI::ImageryComponent*>(self)
VALUE rb_cCeguiImageryComponent;

namespace CeguiImageryComponent
{
/*
 *
 */
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::ImageryComponent);
}

macro_attr(Image,CEGUI::Image*)
macro_attr(ImagePropertySource,CEGUI::String)

macro_attr(VerticalFormatting,CEGUI::VerticalFormatting)
macro_attr(HorizontalFormatting,CEGUI::HorizontalFormatting)

}
/*
 *
*/

void Init_CeguiImageryComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiImageryComponent,"image",1,1);
	rb_define_attr(rb_cCeguiImageryComponent,"imagePropertySource",1,1);

	rb_define_attr(rb_cCeguiImageryComponent,"verticalFormatting",1,1);
	rb_define_attr(rb_cCeguiImageryComponent,"horizontalFormatting",1,1);
	rb_cCeguiComponentBase = rb_define_class_under(rb_mCegui,"ComponentBase",rb_cObject);

#endif

	using namespace CeguiImageryComponent;
	rb_cCeguiImageryComponent = rb_define_class_under(rb_mCegui,"ImageryComponent",rb_cCeguiComponentBase);
	rb_define_alloc_func(rb_cCeguiImageryComponent,_alloc);

	rb_include_module(rb_cCeguiImageryComponent,rb_mEnumerable);

	rb_define_attr_method(rb_cCeguiImageryComponent,"image",_getImage,_setImage);
	rb_define_attr_method(rb_cCeguiImageryComponent,"imagePropertySource",_getImagePropertySource,_setImagePropertySource);

	rb_define_attr_method(rb_cCeguiImageryComponent,"verticalFormatting",_getVerticalFormatting,_setVerticalFormatting);
	rb_define_attr_method(rb_cCeguiImageryComponent,"horizontalFormatting",_getHorizontalFormatting,_setHorizontalFormatting);


}





