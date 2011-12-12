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
	return RubyWindowHolder::get(menubase,rb_cCeguiMenuBase);
}

template <>
inline CEGUI::MenuBase* wrap< CEGUI::MenuBase* >(const VALUE &vmenubase)
{
	if (rb_obj_is_kind_of(vmenubase, rb_cCeguiMenuBase)){
		return (CEGUI::MenuBase*)wrap<CEGUI::Window*>(vmenubase);
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiMenuBase),rb_obj_classname(vmenubase));
		return NULL;
	}
}
#endif /* __RubyCeguiMenuBase_H__ */
