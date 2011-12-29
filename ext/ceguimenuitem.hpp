#ifndef __RubyCeguiMenuItem_H__
#define __RubyCeguiMenuItem_H__

#include "main.hpp"
void Init_CeguiMenuItem(VALUE rb_mCegui);
extern VALUE rb_cCeguiMenuItem;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::MenuItem >(CEGUI::MenuItem *menuitem )
{
	return RubyWindowHolder::get(menuitem,rb_cCeguiMenuItem);
}
template <>
inline CEGUI::MenuItem* wrap< CEGUI::MenuItem* >(const VALUE &vmenuitem)
{
	return unwrapWindow<CEGUI::MenuItem>(vmenuitem, rb_cCeguiMenuItem);
}
#endif /* __RubyCeguiMenuItem_H__ */
