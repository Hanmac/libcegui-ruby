#ifndef __RubyCeguiThumb_H__
#define __RubyCeguiThumb_H__

#include "main.hpp"
void Init_CeguiThumb(VALUE rb_mCegui);
extern VALUE rb_cCeguiThumb;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Thumb >(CEGUI::Thumb *thumb )
{
	if(thumb==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(thumb);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = thumb;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiThumb, NULL, NULL, hold);
		rb_ary_push(rb_windowholder,hold->ruby);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(thumb,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Thumb* wrap< CEGUI::Thumb* >(const VALUE &vthumb)
{
	if (rb_obj_is_kind_of(vthumb, rb_cCeguiThumb)){
		return (CEGUI::Thumb*)(wrap< CEGUI::Window* >(vthumb));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiThumb),rb_obj_classname(vthumb));
		return NULL;
	}
}
#endif /* __RubyCeguiThumb_H__ */
