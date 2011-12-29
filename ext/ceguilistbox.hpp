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
	return RubyWindowHolder::get(listbox,rb_cCeguiListbox);
}

template <>
inline CEGUI::Listbox* wrap< CEGUI::Listbox* >(const VALUE &vlistbox)
{
	return unwrapWindow<CEGUI::Listbox>(vlistbox, rb_cCeguiListbox);
}
#endif /* __RubyCeguiListbox_H__ */
