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
	return unwrapWindow<CEGUI::ItemEntry>(vitementry, rb_cCeguiItemEntry);
}
#endif /* __RubyCeguiItemEntry_H__ */
