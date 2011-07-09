#ifndef __RubyCeguiWindow_H__
#define __RubyCeguiWindow_H__

#include "main.hpp"
void Init_CeguiWindow(VALUE rb_mCegui);
extern VALUE rb_cCeguiWindow;

#include "ceguitooltip.hpp"
template <>
inline VALUE wrap< CEGUI::Window >(CEGUI::Window *window )
{
	if(window==NULL)
		return Qnil;
	CEGUI::Tooltip *tooltip = dynamic_cast<CEGUI::Tooltip*>(window);
	if(tooltip)
		return wrap(tooltip);
	return Data_Wrap_Struct(rb_cCeguiWindow, NULL, NULL, window);
}
template <>
inline void wrap_each<CEGUI::WindowFactory* >(CEGUI::ConstBaseIterator<std::map<CEGUI::String, CEGUI::WindowFactory*, CEGUI::String::FastLessCompare> > it)
{
	for(it.toStart(); !it.isAtEnd(); ++it)
			rb_yield(wrap(it.getCurrentKey()));
}

template <>
inline VALUE wrap< CEGUI::WindowFactoryManager::AliasTargetStack >(const CEGUI::WindowFactoryManager::AliasTargetStack &stack )
{
	return wrap(stack.getActiveTarget());
}
template <>
inline CEGUI::Window* wrap< CEGUI::Window* >(const VALUE &vwindow)
{
	if (rb_obj_is_kind_of(vwindow, rb_cCeguiWindow)){
		CEGUI::Window *window;
		Data_Get_Struct( vwindow, CEGUI::Window, window);
		return window;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiWindow),rb_obj_classname(vwindow));
		return NULL;
	}
}
#endif /* __RubyCeguiWindow_H__ */
