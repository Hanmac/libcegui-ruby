#ifndef __RubyCeguiFrameWindow_H__
#define __RubyCeguiFrameWindow_H__

#include "main.hpp"
void Init_CeguiFrameWindow(VALUE rb_mCegui);
extern VALUE rb_cCeguiFrameWindow;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::FrameWindow >(CEGUI::FrameWindow *framewindow )
{
	return RubyWindowHolder::get(framewindow,rb_cCeguiFrameWindow);
}

template <>
inline CEGUI::FrameWindow* wrap< CEGUI::FrameWindow* >(const VALUE &vframewindow)
{
	return unwrapWindow<CEGUI::FrameWindow>(vframewindow, rb_cCeguiFrameWindow);
}
#endif /* __RubyCeguiFrameWindow_H__ */
