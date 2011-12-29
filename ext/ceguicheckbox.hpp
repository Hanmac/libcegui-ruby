#ifndef __RubyCeguiCheckbox_H__
#define __RubyCeguiCheckbox_H__

#include "main.hpp"
void Init_CeguiCheckbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiCheckbox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Checkbox >(CEGUI::Checkbox *checkbox )
{
	return RubyWindowHolder::get(checkbox,rb_cCeguiCheckbox);
}

template <>
inline CEGUI::Checkbox* wrap< CEGUI::Checkbox* >(const VALUE &vcheckbox)
{
	return unwrapWindow<CEGUI::Checkbox>(vcheckbox, rb_cCeguiCheckbox);
}

#endif /* __RubyCeguiCheckbox_H__ */
