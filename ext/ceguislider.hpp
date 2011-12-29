/*
 * ceguislider.hpp
 *
 *  Created on: 05.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiSlider_H__
#define __RubyCeguiSlider_H__

#include "main.hpp"
void Init_CeguiSlider(VALUE rb_mCegui);
extern VALUE rb_cCeguiSlider;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Slider >(CEGUI::Slider *slider )
{
	return RubyWindowHolder::get(slider,rb_cCeguiSlider);
}

template <>
inline CEGUI::Slider* wrap< CEGUI::Slider* >(const VALUE &vslider)
{
	return unwrapWindow<CEGUI::Slider>(vslider, rb_cCeguiSlider);
}
#endif /* __RubyCeguiSlider_H__ */

