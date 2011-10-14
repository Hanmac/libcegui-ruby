#ifndef __RubyCeguiEditbox_H__
#define __RubyCeguiEditbox_H__

#include "main.hpp"
void Init_CeguiEditbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiEditbox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Editbox >(CEGUI::Editbox *editbox )
{
	if(editbox==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(editbox);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = editbox;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiEditbox, NULL, NULL, hold);
		rb_ary_push(rb_windowholder,hold->ruby);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(editbox,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Editbox* wrap< CEGUI::Editbox* >(const VALUE &veditbox)
{
	if (rb_obj_is_kind_of(veditbox, rb_cCeguiEditbox)){
		return (CEGUI::Editbox*)(wrap< CEGUI::Window* >(veditbox));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiEditbox),rb_obj_classname(veditbox));
		return NULL;
	}
}
#endif /* __RubyCeguiEditbox_H__ */
