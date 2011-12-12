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
	if (rb_obj_is_kind_of(vdefaultwindow, rb_cCeguiDefaultWindow)){
		return (CEGUI::DefaultWindow*)(wrap< CEGUI::Window* >(vdefaultwindow));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiDefaultWindow),rb_obj_classname(vdefaultwindow));
		return NULL;
	}
}
#endif /* __RubyCeguiDefaultWindow_H__ */
