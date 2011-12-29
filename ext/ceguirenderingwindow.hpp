#ifndef __RubyCeguiRenderingWindow_H__
#define __RubyCeguiRenderingWindow_H__

#include "main.hpp"
void Init_CeguiRenderingWindow(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderingWindow;


template <>
inline VALUE wrap< CEGUI::RenderingWindow >(CEGUI::RenderingWindow *window )
{
	if(window==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiRenderingWindow, NULL, NULL, window);
}

template <>
inline CEGUI::RenderingWindow* wrap< CEGUI::RenderingWindow* >(const VALUE &vwindow)
{
	return unwrapPtr<CEGUI::RenderingWindow>(vwindow, rb_cCeguiRenderingWindow);
}
#endif /* __RubyCeguiRenderingWindow_H__ */
