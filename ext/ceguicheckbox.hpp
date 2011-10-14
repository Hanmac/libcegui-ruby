#ifndef __RubyCeguiCheckbox_H__
#define __RubyCeguiCheckbox_H__

#include "main.hpp"
void Init_CeguiCheckbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiCheckbox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Checkbox >(CEGUI::Checkbox *checkbox )
{
	if(checkbox==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(checkbox);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = checkbox;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiCheckbox, NULL, NULL, hold);
		rb_ary_push(rb_windowholder,hold->ruby);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(checkbox,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Checkbox* wrap< CEGUI::Checkbox* >(const VALUE &vcheckbox)
{
	if (rb_obj_is_kind_of(vcheckbox, rb_cCeguiCheckbox)){
		return (CEGUI::Checkbox*)(wrap< CEGUI::Window* >(vcheckbox));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiCheckbox),rb_obj_classname(vcheckbox));
		return NULL;
	}
}

#endif /* __RubyCeguiCheckbox_H__ */
