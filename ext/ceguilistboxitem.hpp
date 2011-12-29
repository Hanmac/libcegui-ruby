#ifndef __RubyCeguiListboxItem_H__
#define __RubyCeguiListboxItem_H__

#include "main.hpp"
void Init_CeguiListboxItem(VALUE rb_mCegui);
extern VALUE rb_cCeguiListboxItem;

#include "ceguilistboxtextitem.hpp"
template <>
inline VALUE wrap< CEGUI::ListboxItem >(CEGUI::ListboxItem *listboxitem )
{
	if(listboxitem==NULL)
		return Qnil;
	CEGUI::ListboxTextItem *listboxtextitem = dynamic_cast<CEGUI::ListboxTextItem*>(listboxitem);
	if(listboxtextitem)
		return wrap(listboxtextitem);
	return Data_Wrap_Struct(rb_cCeguiListboxItem, NULL, NULL, listboxitem);
}

template <>
inline CEGUI::ListboxItem* wrap< CEGUI::ListboxItem* >(const VALUE &vlistboxitem)
{
	if (rb_obj_is_kind_of(vlistboxitem, rb_cString)){
		return wrap< CEGUI::ListboxTextItem* >(vlistboxitem);
	}else
		return unwrapPtr<CEGUI::ListboxItem>(vlistboxitem, rb_cCeguiListboxItem);
}

#endif /* __RubyCeguiListboxItem_H__ */
