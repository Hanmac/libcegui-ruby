#ifndef __RubyCeguiMenubar_H__
#define __RubyCeguiMenubar_H__

#include "main.hpp"
void Init_CeguiMenubar(VALUE rb_mCegui);
extern VALUE rb_cCeguiMenubar;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Menubar >(CEGUI::Menubar *menubar )
{
	if(menubar==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(menubar);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = menubar;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiMenubar, NULL, NULL, menubar);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(menubar,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Menubar* wrap< CEGUI::Menubar* >(const VALUE &vmenubar)
{
	if (rb_obj_is_kind_of(vmenubar, rb_cCeguiMenubar)){
		return (CEGUI::Menubar*)wrap<CEGUI::Window*>(vmenubar);
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiMenubar),rb_obj_classname(vmenubar));
		return NULL;
	}
}
#endif /* __RubyCeguiMenubar_H__ */
