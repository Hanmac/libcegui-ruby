/*
 * ceguiframecomponent.cpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */


#include "ceguicomponentbase.hpp"
#include "ceguifalagardenums.hpp"
#include "ceguiexception.hpp"

#include "ceguiimage.hpp"

#define _self wrap<CEGUI::FrameComponent*>(self)
VALUE rb_cCeguiFrameComponent;

namespace CeguiFrameComponent
{
/*
 *
 */
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::FrameComponent);
}

macro_attr(BackgroundVerticalFormatting,CEGUI::VerticalFormatting)
macro_attr(BackgroundHorizontalFormatting,CEGUI::HorizontalFormatting)


VALUE _get(VALUE self,VALUE component)
{
	return wrap(_self->getImage(wrap<CEGUI::FrameImageComponent>(component)));
}
VALUE _set(VALUE self,VALUE component,VALUE image)
{
	_self->setImage(wrap<CEGUI::FrameImageComponent>(component),wrap<CEGUI::Image*>(image));
	return self;
}

VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for(unsigned int i = 0;i<CEGUI::FIC_FRAME_IMAGE_COUNT;++i)
	{
		rb_yield_values(2,wrap((CEGUI::FrameImageComponent)i),wrap(_self->getImage((CEGUI::FrameImageComponent)i)));
	}
	return self;
}


}
/*
 *
*/

void Init_CeguiFrameComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiFrameComponent,"backgroundVerticalFormatting",1,1);
	rb_define_attr(rb_cCeguiFrameComponent,"backgroundHorizontalFormatting",1,1);
	rb_cCeguiComponentBase = rb_define_class_under(rb_mCegui,"ComponentBase",rb_cObject);

#endif

	using namespace CeguiFrameComponent;
	rb_cCeguiFrameComponent = rb_define_class_under(rb_mCegui,"FrameComponent",rb_cCeguiComponentBase);
	rb_define_alloc_func(rb_cCeguiFrameComponent,_alloc);

	rb_include_module(rb_cCeguiFrameComponent,rb_mEnumerable);

	rb_define_method(rb_cCeguiFrameComponent,"each",RUBY_METHOD_FUNC(_each),0);

	rb_define_method(rb_cCeguiFrameComponent,"[]",RUBY_METHOD_FUNC(_get),1);
	rb_define_method(rb_cCeguiFrameComponent,"[]=",RUBY_METHOD_FUNC(_set),2);

	rb_define_attr_method(rb_cCeguiFrameComponent,"backgroundVerticalFormatting",_getBackgroundVerticalFormatting,_setBackgroundVerticalFormatting);
	rb_define_attr_method(rb_cCeguiFrameComponent,"backgroundHorizontalFormatting",_getBackgroundHorizontalFormatting,_setBackgroundHorizontalFormatting);


}

