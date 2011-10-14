#ifndef __RubyCeguiListbox_H__
#define __RubyCeguiListbox_H__

#include "main.hpp"
void Init_CeguiListbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiListbox;

#include "ceguicombodroplist.hpp"

template <>
inline VALUE wrap< CEGUI::Listbox >(CEGUI::Listbox *listbox )
{
	if(listbox==NULL)
		return Qnil;
	CEGUI::ComboDropList *combodroplist = dynamic_cast<CEGUI::ComboDropList*>(listbox);
	if(combodroplist)
		return wrap(combodroplist);
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(listbox);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = listbox;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiListbox, NULL, NULL, hold);
		rb_ary_push(rb_windowholder,hold->ruby);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(listbox,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Listbox* wrap< CEGUI::Listbox* >(const VALUE &vlistbox)
{
	if (rb_obj_is_kind_of(vlistbox, rb_cCeguiListbox)){
		return (CEGUI::Listbox*)(wrap< CEGUI::Window* >(vlistbox));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiListbox),rb_obj_classname(vlistbox));
		return NULL;
	}
}
#endif /* __RubyCeguiListbox_H__ */
