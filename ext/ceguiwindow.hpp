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
inline void wrap_each<CEGUI::WindowFactory* >(CEGUI::ConstBaseIterator<std::map<CEGUI::String, CEGUI::WindowFactory*, CEGUI::String::FastLessCompare> > it)
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
