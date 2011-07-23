#ifndef __RubyCeguiListboxTextItem_H__
#define __RubyCeguiListboxTextItem_H__

#include "main.hpp"
void Init_CeguiListboxTextItem(VALUE rb_mCegui);
extern VALUE rb_cCeguiListboxTextItem;

template <>
inline VALUE wrap< CEGUI::ListboxTextItem >(CEGUI::ListboxTextItem *listboxtextitem )
{
	if(listboxtextitem==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiListboxTextItem, NULL, NULL, listboxtextitem);
}

template <>
inline CEGUI::ListboxTextItem* wrap< CEGUI::ListboxTextItem* >(const VALUE &vlistboxtextitem)
{
	if (rb_obj_is_kind_of(vlistboxtextitem, rb_cCeguiListboxItem)){
		CEGUI::ListboxTextItem *listboxtextitem;
		Data_Get_Struct( vlistboxtextitem, CEGUI::ListboxTextItem, listboxtextitem);
		return listboxtextitem;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiListboxTextItem),rb_obj_classname(vlistboxtextitem));
		return NULL;
	}
}
#endif /* __RubyCeguiListboxItem_H__ */
