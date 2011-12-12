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
	if (rb_obj_is_kind_of(vmenubar, rb_cCeguiMenubar)){
		return (CEGUI::Menubar*)wrap<CEGUI::Window*>(vmenubar);
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiMenubar),rb_obj_classname(vmenubar));
		return NULL;
	}
}
#endif /* __RubyCeguiMenubar_H__ */
