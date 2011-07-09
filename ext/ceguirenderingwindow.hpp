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
	if (rb_obj_is_kind_of(vwindow, rb_cCeguiRenderingWindow)){
		CEGUI::RenderingWindow *window;
		Data_Get_Struct( vwindow, CEGUI::RenderingWindow, window);
		return window;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiRenderingWindow),rb_obj_classname(vwindow));
		return NULL;
	}
}
#endif /* __RubyCeguiRenderingWindow_H__ */
