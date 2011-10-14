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
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(itementry);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = itementry;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiItemEntry, NULL, NULL, hold);
		rb_ary_push(rb_windowholder,hold->ruby);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(itementry,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::ItemEntry* wrap< CEGUI::ItemEntry* >(const VALUE &vitementry)
{
	if (rb_obj_is_kind_of(vitementry, rb_cCeguiItemEntry)){
		return (CEGUI::ItemEntry*)(wrap< CEGUI::ItemEntry* >(vitementry));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiItemEntry),rb_obj_classname(vitementry));
		return NULL;
	}
}
#endif /* __RubyCeguiItemEntry_H__ */
