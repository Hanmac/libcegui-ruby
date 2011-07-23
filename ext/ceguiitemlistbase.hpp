#ifndef __RubyCeguiItemListBase_H__
#define __RubyCeguiItemListBase_H__

#include "main.hpp"
void Init_CeguiItemListBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiItemListBase;

#include "ceguimenubase.hpp"

template <>
inline VALUE wrap< CEGUI::ItemListBase >(CEGUI::ItemListBase *itemlistbase )
{
	if(itemlistbase==NULL)
		return Qnil;
	CEGUI::MenuBase *menubase = dynamic_cast<CEGUI::MenuBase*>(itemlistbase);
	if(menubase)
		return wrap(menubase);
	return Data_Wrap_Struct(rb_cCeguiItemListBase, NULL, NULL, itemlistbase);
}

template <>
inline CEGUI::ItemListBase* wrap< CEGUI::ItemListBase* >(const VALUE &vitemlistbase)
{
	if (rb_obj_is_kind_of(vitemlistbase, rb_cCeguiItemListBase)){
		CEGUI::ItemListBase *itemlistbase;
		Data_Get_Struct( vitemlistbase, CEGUI::ItemListBase, itemlistbase);
		return itemlistbase;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiItemListBase),rb_obj_classname(vitemlistbase));
		return NULL;
	}
}
#endif /* __RubyCeguiItemListBase_H__ */
