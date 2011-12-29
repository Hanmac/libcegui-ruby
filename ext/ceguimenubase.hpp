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
	return unwrapWindow<CEGUI::MenuBase>(vmenubase, rb_cCeguiMenuBase);
}
#endif /* __RubyCeguiMenuBase_H__ */
