#ifndef __RubyCeguiWidgetLook_H__
#define __RubyCeguiWidgetLook_H__

#include "main.hpp"
void Init_CeguiWidgetLook(VALUE rb_mCegui);
extern VALUE rb_cCeguiWidgetLook;

template <>
inline VALUE wrap< CEGUI::WidgetLookFeel >(CEGUI::WidgetLookFeel *look )
{
	if(look==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiWidgetLook, NULL, NULL, look);
}
template <>
inline CEGUI::WidgetLookFeel* wrap< CEGUI::WidgetLookFeel* >(const VALUE &vlook)
{
	if (rb_obj_is_kind_of(vlook, rb_cCeguiWidgetLook)){
		CEGUI::WidgetLookFeel *look;
		Data_Get_Struct( vlook, CEGUI::WidgetLookFeel, look);
		return look;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiWidgetLook),rb_obj_classname(vlook));
		return NULL;
	}
}
#endif /* __RubyCeguiWidgetLook_H__ */
