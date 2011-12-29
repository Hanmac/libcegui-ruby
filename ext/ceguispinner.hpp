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
	return unwrapWindow<CEGUI::Spinner>(vspinner, rb_cCeguiSpinner);
}
#endif /* __RubyCeguiSpinner_H__ */


