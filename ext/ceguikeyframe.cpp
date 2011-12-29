/*
 * ceguikeyframe.cpp
 *
 *  Created on: 21.12.2011
 *      Author: hanmac
 */

#define _self wrap<CEGUI::KeyFrame*>(self)

#include "ceguikeyframe.hpp"
#include "ceguiexception.hpp"

VALUE rb_cCeguiKeyFrame;
namespace CeguiKeyFrame {

singlereturn(getPosition)

macro_attr(Value,CEGUI::String)
macro_attr(SourceProperty,CEGUI::String)
macro_attr(Progression,CEGUI::KeyFrame::Progression)



}
/*
 *
 */
void Init_CeguiKeyFrame(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

#endif
	using namespace CeguiKeyFrame;

	rb_cCeguiKeyFrame = rb_define_class_under(rb_mCegui,"KeyFrame",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiKeyFrame);

}




