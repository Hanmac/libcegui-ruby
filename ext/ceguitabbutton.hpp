/*
 * ceguitabbutton.hpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiTabButton_H__
#define __RubyCeguiTabButton_H__

#include "main.hpp"
void Init_CeguiTabButton(VALUE rb_mCegui);
extern VALUE rb_cCeguiTabButton;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::TabButton >(CEGUI::TabButton *tabbutton )
{
	return RubyWindowHolder::get(tabbutton,rb_cCeguiTabButton);
}

template <>
inline CEGUI::TabButton* wrap< CEGUI::TabButton* >(const VALUE &vtabbutton)
{
	return unwrapWindow<CEGUI::TabButton>(vtabbutton, rb_cCeguiTabButton);
}
#endif /* __RubyCeguiTabButton_H__ */
