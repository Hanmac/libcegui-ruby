#ifndef __RubyCeguiMenuItem_H__
#define __RubyCeguiMenuItem_H__

#include "main.hpp"
void Init_CeguiMenuItem(VALUE rb_mCegui);
extern VALUE rb_cCeguiMenuItem;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::MenuItem >(CEGUI::MenuItem *menuitem )
{
	return RubyWindowHolder::get(menuitem,rb_cCeguiMenuItem);
}
template <>
inline CEGUI::MenuItem* wrap< CEGUI::MenuItem* >(const VALUE &vmenuitem)
{
	if (rb_obj_is_kind_of(vmenuitem, rb_cCeguiMenuItem)){
		return (CEGUI::MenuItem*)(wrap< CEGUI::Window* >(vmenuitem));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiMenuItem),rb_obj_classname(vmenuitem));
		return NULL;
	}
}
#endif /* __RubyCeguiMenuItem_H__ */
