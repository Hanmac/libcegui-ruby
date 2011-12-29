#ifndef __RubyCeguiCombobox_H__
#define __RubyCeguiCombobox_H__

#include "main.hpp"
void Init_CeguiCombobox(VALUE rb_mCegui);
extern VALUE rb_cCeguiCombobox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Combobox >(CEGUI::Combobox *box )
{
	return RubyWindowHolder::get(box,rb_cCeguiCombobox);
}

template <>
inline CEGUI::Combobox* wrap< CEGUI::Combobox* >(const VALUE &vbox)
{
	return unwrapWindow<CEGUI::Combobox>(vbox, rb_cCeguiCombobox);
}
#endif /* __RubyCeguiCombobox_H__ */
