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
	return unwrapWindow<CEGUI::ProgressBar>(vprogressbar, rb_cCeguiProgressBar);
}
#endif /* __RubyCeguiProgressBar_H__ */

