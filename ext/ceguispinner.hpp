/*
 * ceguispinner.hpp
 *
 *  Created on: 05.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiSpinner_H__
#define __RubyCeguiSpinner_H__

#include "main.hpp"
void Init_CeguiSpinner(VALUE rb_mCegui);
extern VALUE rb_cCeguiSpinner;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Spinner >(CEGUI::Spinner *spinner )
{
	return RubyWindowHolder::get(spinner,rb_cCeguiSpinner);
}

template <>
inline CEGUI::Spinner* wrap< CEGUI::Spinner* >(const VALUE &vspinner)
{
	if (rb_obj_is_kind_of(vspinner, rb_cCeguiSpinner)){
		return (CEGUI::Spinner*)(wrap< CEGUI::Window* >(vspinner));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiSpinner),rb_obj_classname(vspinner));
		return NULL;
	}
}
#endif /* __RubyCeguiSpinner_H__ */


