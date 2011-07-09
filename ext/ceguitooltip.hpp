#ifndef __RubyCeguiTooltip_H__
#define __RubyCeguiTooltip_H__

#include "main.hpp"
void Init_CeguiTooltip(VALUE rb_mCegui);
extern VALUE rb_cCeguiTooltip;


template <>
inline VALUE wrap< CEGUI::Tooltip >(CEGUI::Tooltip *tooltip )
{
	if(tooltip==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiTooltip, NULL, NULL, tooltip);
}

template <>
inline CEGUI::Tooltip* wrap< CEGUI::Tooltip* >(const VALUE &vtooltip)
{
	if (rb_obj_is_kind_of(vtooltip, rb_cCeguiTooltip)){
		CEGUI::Tooltip *tooltip;
		Data_Get_Struct( vtooltip, CEGUI::Tooltip, tooltip);
		return tooltip;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiTooltip),rb_obj_classname(vtooltip));
		return NULL;
	}
}
#endif /* __RubyCeguiTooltip_H__ */
