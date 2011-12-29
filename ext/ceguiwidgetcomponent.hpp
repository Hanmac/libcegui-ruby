/*
 * ceguiwidgetcomponent.hpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiWidgetComponent_H__
#define __RubyCeguiWidgetComponent_H__

#include "main.hpp"
void Init_CeguiWidgetComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiWidgetComponent;

template <>
inline VALUE wrap< CEGUI::WidgetComponent >(CEGUI::WidgetComponent *look )
{
	if(look==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiWidgetComponent, NULL, NULL, look);
}
template <>
inline CEGUI::WidgetComponent* wrap< CEGUI::WidgetComponent* >(const VALUE &vlook)
{
	return unwrapPtr<CEGUI::WidgetComponent>(vlook, rb_cCeguiWidgetComponent);
}
#endif /* __RubyCeguiWidgetComponent_H__ */
