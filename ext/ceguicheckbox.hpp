#ifndef __RubyCeguiCheckbox_H__
#define __RubyCeguiCheckbox_H__

#include "main.hpp"
void Init_CeguiCheckbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiCheckbox;


template <>
inline VALUE wrap< CEGUI::Checkbox >(CEGUI::Checkbox *checkbox )
{
	if(checkbox==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiCheckbox, NULL, NULL, checkbox);
}

template <>
inline CEGUI::Checkbox* wrap< CEGUI::Checkbox* >(const VALUE &vcheckbox)
{
	if (rb_obj_is_kind_of(vcheckbox, rb_cCeguiCheckbox)){
		CEGUI::Checkbox *checkbox;
		Data_Get_Struct( vcheckbox, CEGUI::Checkbox, checkbox);
		return checkbox;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiCheckbox),rb_obj_classname(vcheckbox));
		return NULL;
	}
}
#endif /* __RubyCeguiCheckbox_H__ */
