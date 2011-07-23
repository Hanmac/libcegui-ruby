#ifndef __RubyCeguiScrollbar_H__
#define __RubyCeguiScrollbar_H__

#include "main.hpp"
void Init_CeguiScrollbar(VALUE rb_mCegui);
extern VALUE rb_cCeguiScrollbar;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Scrollbar >(CEGUI::Scrollbar *scrollbar )
{
	if(scrollbar==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(scrollbar);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = scrollbar;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiScrollbar, NULL, NULL, hold);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(scrollbar,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Scrollbar* wrap< CEGUI::Scrollbar* >(const VALUE &vscrollbar)
{
	if (rb_obj_is_kind_of(vscrollbar, rb_cCeguiScrollbar)){
		return (CEGUI::Scrollbar*)(wrap< CEGUI::Window* >(vscrollbar));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiScrollbar),rb_obj_classname(vscrollbar));
		return NULL;
	}
}
#endif /* __RubyCeguiScrollbar_H__ */
