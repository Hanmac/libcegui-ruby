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
	if (rb_obj_is_kind_of(vitem, rb_cCeguiTreeItem)){
		CEGUI::TreeItem *item;
		Data_Get_Struct( vitem, CEGUI::TreeItem, item);
		return item;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiTreeItem),rb_obj_classname(vitem));
		return NULL;
	}
}
#endif /* __RubyCeguiTree_H__ */
