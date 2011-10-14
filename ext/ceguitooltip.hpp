#ifndef __RubyCeguiTooltip_H__
#define __RubyCeguiTooltip_H__

#include "main.hpp"
void Init_CeguiTooltip(VALUE rb_mCegui);
extern VALUE rb_cCeguiTooltip;


#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Tooltip >(CEGUI::Tooltip *tooltip )
{
	if(tooltip==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(tooltip);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = tooltip;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiTooltip, NULL, NULL, hold);
		rb_ary_push(rb_windowholder,hold->ruby);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(tooltip,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Tooltip* wrap< CEGUI::Tooltip* >(const VALUE &vtooltip)
{
	if (rb_obj_is_kind_of(vtooltip, rb_cCeguiTooltip)){
		return (CEGUI::Tooltip*)(wrap< CEGUI::Window* >(vtooltip));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiTooltip),rb_obj_classname(vtooltip));
		return NULL;
	}
}
#endif /* __RubyCeguiTooltip_H__ */
