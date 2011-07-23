#ifndef __RubyCeguiPopupMenu_H__
#define __RubyCeguiPopupMenu_H__

#include "main.hpp"
void Init_CeguiPopupMenu(VALUE rb_mCegui);
extern VALUE rb_cCeguiPopupMenu;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::PopupMenu >(CEGUI::PopupMenu *popupmenu )
{
	if(popupmenu==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(popupmenu);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = popupmenu;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiPopupMenu, NULL, NULL, popupmenu);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(popupmenu,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::PopupMenu* wrap< CEGUI::PopupMenu* >(const VALUE &vpopupmenu)
{
	if (rb_obj_is_kind_of(vpopupmenu, rb_cCeguiPopupMenu)){
		return (CEGUI::PopupMenu*)wrap<CEGUI::Window*>(vpopupmenu);
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiPopupMenu),rb_obj_classname(vpopupmenu));
		return NULL;
	}
}
#endif /* __RubyCeguiPopupMenu_H__ */
