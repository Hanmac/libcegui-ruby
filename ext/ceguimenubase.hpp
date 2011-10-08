#ifndef __RubyCeguiMenuBase_H__
#define __RubyCeguiMenuBase_H__

#include "main.hpp"
void Init_CeguiMenuBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiMenuBase;

#include "ceguipopupmenu.hpp"
#include "ceguimenubar.hpp"
template <>
inline VALUE wrap< CEGUI::MenuBase >(CEGUI::MenuBase *menubase )
{
	if(menubase==NULL)
		return Qnil;
	CEGUI::PopupMenu *popupmenu = dynamic_cast<CEGUI::PopupMenu*>(menubase);
	if(popupmenu)
		return wrap(popupmenu);
	CEGUI::Menubar *menubar = dynamic_cast<CEGUI::Menubar*>(menubase);
	if(menubar)
		return wrap(menubar);
	
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(menubase);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = menubase;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiMenuBase, NULL, NULL, menubase);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(menubase,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::MenuBase* wrap< CEGUI::MenuBase* >(const VALUE &vmenubase)
{
	if (rb_obj_is_kind_of(vmenubase, rb_cCeguiMenuBase)){
		return (CEGUI::MenuBase*)wrap<CEGUI::Window*>(vmenubase);
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiMenuBase),rb_obj_classname(vmenubase));
		return NULL;
	}
}
#endif /* __RubyCeguiMenuBase_H__ */
