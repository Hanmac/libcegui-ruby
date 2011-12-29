#ifndef __RubyCeguiEditbox_H__
#define __RubyCeguiEditbox_H__

#include "main.hpp"
void Init_CeguiEditbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiEditbox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Editbox >(CEGUI::Editbox *editbox )
{
	return RubyWindowHolder::get(editbox,rb_cCeguiEditbox);
}

template <>
inline CEGUI::Editbox* wrap< CEGUI::Editbox* >(const VALUE &veditbox)
{
	return unwrapWindow<CEGUI::Editbox>(veditbox, rb_cCeguiEditbox);
}
#endif /* __RubyCeguiEditbox_H__ */
