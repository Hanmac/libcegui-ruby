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
	return unwrapPtr<CEGUI::WidgetLookFeel>(vlook, rb_cCeguiWidgetLook);
}
#endif /* __RubyCeguiWidgetLook_H__ */
