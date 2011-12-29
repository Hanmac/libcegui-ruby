#ifndef __RubyCeguiTreeItem_H__
#define __RubyCeguiTreeItem_H__

#include "main.hpp"
void Init_CeguiTreeItem(VALUE rb_mCegui);
extern VALUE rb_cCeguiTreeItem;


template <>
inline VALUE wrap< CEGUI::TreeItem >(CEGUI::TreeItem *item )
{
	if(item==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiTreeItem, NULL, NULL, item);
}

template <>
inline CEGUI::TreeItem* wrap< CEGUI::TreeItem* >(const VALUE &vitem)
{
	return unwrapPtr<CEGUI::TreeItem>(vitem, rb_cCeguiTreeItem);
}
#endif /* __RubyCeguiTree_H__ */
