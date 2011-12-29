#ifndef __RubyCeguiMenubar_H__
#define __RubyCeguiMenubar_H__

#include "main.hpp"
void Init_CeguiMenubar(VALUE rb_mCegui);
extern VALUE rb_cCeguiMenubar;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Menubar >(CEGUI::Menubar *menubar )
{
	return RubyWindowHolder::get(menubar,rb_cCeguiMenubar);
}

template <>
inline CEGUI::Menubar* wrap< CEGUI::Menubar* >(const VALUE &vmenubar)
{
	return unwrapWindow<CEGUI::Menubar>(vmenubar, rb_cCeguiMenubar);
}
#endif /* __RubyCeguiMenubar_H__ */
