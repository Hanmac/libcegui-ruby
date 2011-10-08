#ifndef __RubyCeguiWindow_H__
#define __RubyCeguiWindow_H__

#include "main.hpp"
void Init_CeguiWindow(VALUE rb_mCegui);

#include "ceguiwindowimpl.hpp"

#include "ceguitooltip.hpp"
#include "ceguilistbox.hpp"
#include "ceguiscrollbar.hpp"
#include "ceguiitementry.hpp"
#include "ceguibuttonbase.hpp"

#include "ceguiitemlistbase.hpp"

#include "ceguieditbox.hpp"
#include "ceguicombobox.hpp"
#include "ceguitree.hpp"
template <>
inline VALUE wrap< CEGUI::Window >(CEGUI::Window *window )
{
	if(window==NULL)
		return Qnil;

	CEGUI::Tooltip *tooltip = dynamic_cast<CEGUI::Tooltip*>(window);
	if(tooltip)
		return wrap(tooltip);
	CEGUI::Listbox *listbox = dynamic_cast<CEGUI::Listbox*>(window);
	if(listbox)
		return wrap(listbox);
	CEGUI::Scrollbar *scrollbar = dynamic_cast<CEGUI::Scrollbar*>(window);
	if(scrollbar)
		return wrap(scrollbar);
	CEGUI::ItemEntry *itementry = dynamic_cast<CEGUI::ItemEntry*>(window);
	if(itementry)
		return wrap(itementry);

	CEGUI::ButtonBase *buttonbase = dynamic_cast<CEGUI::ButtonBase*>(window);
	if(buttonbase)
		return wrap(buttonbase);
	CEGUI::ItemListBase *itemlistbase = dynamic_cast<CEGUI::ItemListBase*>(window);
	if(itemlistbase)
		return wrap(itemlistbase);
	CEGUI::Editbox *editbox = dynamic_cast<CEGUI::Editbox*>(window);
	if(editbox)
		return wrap(editbox);
	CEGUI::Combobox *combobox = dynamic_cast<CEGUI::Combobox*>(window);
	if(combobox)
		return wrap(combobox);

	CEGUI::Tree *tree = dynamic_cast<CEGUI::Tree*>(window);
	if(tree)
		return wrap(tree);

	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(window);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = window;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiWindow, NULL, NULL, hold);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(window,hold));
		return hold->ruby;
	}
}
template <>
inline void wrap_each<CEGUI::WindowFactory* >(CEGUI::ConstMapIterator<std::map<CEGUI::String, CEGUI::WindowFactory*, CEGUI::StringFastLessCompare> > it)
{
	for(it.toStart(); !it.isAtEnd(); ++it)
			rb_yield(wrap(it.getCurrentKey()));
}

template <>
inline VALUE wrap< CEGUI::WindowFactoryManager::AliasTargetStack >(const CEGUI::WindowFactoryManager::AliasTargetStack &stack )
{
	return wrap(stack.getActiveTarget());
}
#endif /* __RubyCeguiWindow_H__ */
