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
	if (rb_obj_is_kind_of(vslider, rb_cCeguiSlider)){
		return (CEGUI::Slider*)(wrap< CEGUI::Window* >(vslider));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiSlider),rb_obj_classname(vslider));
		return NULL;
	}
}
#endif /* __RubyCeguiSlider_H__ */

