/*
 * ceguimultilineeditbox.hpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiMultiLineEditbox_H__
#define __RubyCeguiMultiLineEditbox_H__

#include "main.hpp"
void Init_CeguiMultiLineEditbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiMultiLineEditbox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::MultiLineEditbox >(CEGUI::MultiLineEditbox *editbox )
{
	return RubyWindowHolder::get(editbox,rb_cCeguiMultiLineEditbox);
}

template <>
inline CEGUI::MultiLineEditbox* wrap< CEGUI::MultiLineEditbox* >(const VALUE &veditbox)
{
	return unwrapWindow<CEGUI::MultiLineEditbox>(veditbox, rb_cCeguiMultiLineEditbox);
}
#endif /* __RubyCeguiEditbox_H__ */
