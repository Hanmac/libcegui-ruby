#ifndef __RubyCeguiListbox_H__
#define __RubyCeguiListbox_H__

#include "main.hpp"
void Init_CeguiListbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiListbox;


template <>
inline VALUE wrap< CEGUI::Listbox >(CEGUI::Listbox *listbox )
{
	if(listbox==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiListbox, NULL, NULL, listbox);
}

template <>
inline CEGUI::Listbox* wrap< CEGUI::Listbox* >(const VALUE &vlistbox)
{
	if (rb_obj_is_kind_of(vlistbox, rb_cCeguiListbox)){
		CEGUI::Listbox *listbox;
		Data_Get_Struct( vlistbox, CEGUI::Listbox, listbox);
		return listbox;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiListbox),rb_obj_classname(vlistbox));
		return NULL;
	}
}
#endif /* __RubyCeguiListbox_H__ */
