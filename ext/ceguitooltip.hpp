#ifndef __RubyCeguiTooltip_H__
#define __RubyCeguiTooltip_H__

#include "main.hpp"
void Init_CeguiTooltip(VALUE rb_mCegui);
extern VALUE rb_cCeguiTooltip;


#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Tooltip >(CEGUI::Tooltip *tooltip )
{
	return RubyWindowHolder::get(tooltip,rb_cCeguiTooltip);
}

template <>
inline CEGUI::Tooltip* wrap< CEGUI::Tooltip* >(const VALUE &vtooltip)
{
	if (rb_obj_is_kind_of(vtooltip, rb_cCeguiTooltip)){
		return (CEGUI::Tooltip*)(wrap< CEGUI::Window* >(vtooltip));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiTooltip),rb_obj_classname(vtooltip));
		return NULL;
	}
}
#endif /* __RubyCeguiTooltip_H__ */
