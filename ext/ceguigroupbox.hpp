/*
 * ceguigroupbox.hpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiGroupBox_H__
#define __RubyCeguiGroupBox_H__

#include "main.hpp"
void Init_CeguiGroupBox(VALUE rb_mCegui);
extern VALUE rb_cCeguiGroupBox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::GroupBox >(CEGUI::GroupBox *groupbox )
{
	return RubyWindowHolder::get(groupbox,rb_cCeguiGroupBox);
}

template <>
inline CEGUI::GroupBox* wrap< CEGUI::GroupBox* >(const VALUE &vgroupbox)
{
	return unwrapWindow<CEGUI::GroupBox>(vgroupbox, rb_cCeguiGroupBox);
}
#endif /* __RubyCeguiGroupBox_H__ */
