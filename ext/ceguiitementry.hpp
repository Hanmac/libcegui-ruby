#ifndef __RubyCeguiItemEntry_H__
#define __RubyCeguiItemEntry_H__

#include "main.hpp"
void Init_CeguiItemEntry(VALUE rb_mCegui);
extern VALUE rb_cCeguiItemEntry;

#include "ceguimenuitem.hpp"

template <>
inline VALUE wrap< CEGUI::ItemEntry >(CEGUI::ItemEntry *itementry )
{
	if(itementry==NULL)
		return Qnil;
	CEGUI::MenuItem *menuitem = dynamic_cast<CEGUI::MenuItem*>(itementry);
	if(menuitem)
		return wrap(menuitem);
	return RubyWindowHolder::get(itementry,rb_cCeguiItemEntry);
}

template <>
inline CEGUI::ItemEntry* wrap< CEGUI::ItemEntry* >(const VALUE &vitementry)
{
	if (rb_obj_is_kind_of(vitementry, rb_cCeguiItemEntry)){
		return (CEGUI::ItemEntry*)(wrap< CEGUI::ItemEntry* >(vitementry));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiItemEntry),rb_obj_classname(vitementry));
		return NULL;
	}
}
#endif /* __RubyCeguiItemEntry_H__ */
