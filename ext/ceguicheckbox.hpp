#ifndef __RubyCeguiCheckbox_H__
#define __RubyCeguiCheckbox_H__

#include "main.hpp"
void Init_CeguiCheckbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiCheckbox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Checkbox >(CEGUI::Checkbox *checkbox )
{
	return RubyWindowHolder::get(checkbox,rb_cCeguiCheckbox);
}

template <>
inline CEGUI::Checkbox* wrap< CEGUI::Checkbox* >(const VALUE &vcheckbox)
{
	if (rb_obj_is_kind_of(vcheckbox, rb_cCeguiCheckbox)){
		return (CEGUI::Checkbox*)(wrap< CEGUI::Window* >(vcheckbox));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiCheckbox),rb_obj_classname(vcheckbox));
		return NULL;
	}
}

#endif /* __RubyCeguiCheckbox_H__ */
