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
	if (rb_obj_is_kind_of(vframewindow, rb_cCeguiFrameWindow)){
		return (CEGUI::FrameWindow*)(wrap< CEGUI::Window* >(vframewindow));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiFrameWindow),rb_obj_classname(vframewindow));
		return NULL;
	}
}
#endif /* __RubyCeguiFrameWindow_H__ */
