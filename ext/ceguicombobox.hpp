#ifndef __RubyCeguiCombobox_H__
#define __RubyCeguiCombobox_H__

#include "main.hpp"
void Init_CeguiCombobox(VALUE rb_mCegui);
extern VALUE rb_cCeguiCombobox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Combobox >(CEGUI::Combobox *box )
{
	return RubyWindowHolder::get(box,rb_cCeguiCombobox);
}

template <>
inline CEGUI::Combobox* wrap< CEGUI::Combobox* >(const VALUE &vbox)
{
	if(rb_obj_is_kind_of(vbox, rb_cCeguiCombobox)){
		return (CEGUI::Combobox*)(wrap< CEGUI::Window* >(vbox));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiCombobox),rb_obj_classname(vbox));
		return NULL;
	}
}
#endif /* __RubyCeguiCombobox_H__ */
