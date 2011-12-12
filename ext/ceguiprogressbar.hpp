/*
 * ceguiprogressbar.hpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiProgressBar_H__
#define __RubyCeguiProgressBar_H__

#include "main.hpp"
void Init_CeguiProgressBar(VALUE rb_mCegui);
extern VALUE rb_cCeguiProgressBar;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::ProgressBar >(CEGUI::ProgressBar *progressbar )
{
	return RubyWindowHolder::get(progressbar,rb_cCeguiProgressBar);
}

template <>
inline CEGUI::ProgressBar* wrap< CEGUI::ProgressBar* >(const VALUE &vprogressbar)
{
	if (rb_obj_is_kind_of(vprogressbar, rb_cCeguiProgressBar)){
		return (CEGUI::ProgressBar*)(wrap< CEGUI::Window* >(vprogressbar));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiProgressBar),rb_obj_classname(vprogressbar));
		return NULL;
	}
}
#endif /* __RubyCeguiProgressBar_H__ */

