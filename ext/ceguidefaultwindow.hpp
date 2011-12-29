#ifndef __RubyCeguiDefaultWindow_H__
#define __RubyCeguiDefaultWindow_H__

#include "main.hpp"
void Init_CeguiDefaultWindow(VALUE rb_mCegui);
extern VALUE rb_cCeguiDefaultWindow;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::DefaultWindow >(CEGUI::DefaultWindow *defaultwindow )
{
	return RubyWindowHolder::get(defaultwindow,rb_cCeguiDefaultWindow);
}

template <>
inline CEGUI::DefaultWindow* wrap< CEGUI::DefaultWindow* >(const VALUE &vdefaultwindow)
{
	return unwrapWindow<CEGUI::DefaultWindow>(vdefaultwindow, rb_cCeguiDefaultWindow);
}
#endif /* __RubyCeguiDefaultWindow_H__ */
