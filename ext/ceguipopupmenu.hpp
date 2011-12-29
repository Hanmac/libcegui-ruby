#ifndef __RubyCeguiPopupMenu_H__
#define __RubyCeguiPopupMenu_H__

#include "main.hpp"
void Init_CeguiPopupMenu(VALUE rb_mCegui);
extern VALUE rb_cCeguiPopupMenu;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::PopupMenu >(CEGUI::PopupMenu *popupmenu )
{
	return RubyWindowHolder::get(popupmenu,rb_cCeguiPopupMenu);
}

template <>
inline CEGUI::PopupMenu* wrap< CEGUI::PopupMenu* >(const VALUE &vpopupmenu)
{
	return unwrapWindow<CEGUI::PopupMenu>(vpopupmenu, rb_cCeguiPopupMenu);
}
#endif /* __RubyCeguiPopupMenu_H__ */
