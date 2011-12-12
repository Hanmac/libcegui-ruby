#ifndef __RubyCeguiScrollbar_H__
#define __RubyCeguiScrollbar_H__

#include "main.hpp"
void Init_CeguiScrollbar(VALUE rb_mCegui);
extern VALUE rb_cCeguiScrollbar;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Scrollbar >(CEGUI::Scrollbar *scrollbar )
{
	return RubyWindowHolder::get(scrollbar,rb_cCeguiScrollbar);
}

template <>
inline CEGUI::Scrollbar* wrap< CEGUI::Scrollbar* >(const VALUE &vscrollbar)
{
	if (rb_obj_is_kind_of(vscrollbar, rb_cCeguiScrollbar)){
		return (CEGUI::Scrollbar*)(wrap< CEGUI::Window* >(vscrollbar));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiScrollbar),rb_obj_classname(vscrollbar));
		return NULL;
	}
}
#endif /* __RubyCeguiScrollbar_H__ */
