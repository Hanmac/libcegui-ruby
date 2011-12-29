/*
 * ceguitextcomponent.hpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiTextComponent_H__
#define __RubyCeguiTextComponent_H__

#include "main.hpp"
void Init_CeguiTextComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiTextComponent;


template <>
inline VALUE wrap< CEGUI::TextComponent >(CEGUI::TextComponent *textcomponent )
{
	return Data_Wrap_Struct(rb_cCeguiTextComponent, NULL, NULL, textcomponent);
}

template <>
inline CEGUI::TextComponent* wrap< CEGUI::TextComponent* >(const VALUE &vtextcomponent)
{
	return unwrapPtr<CEGUI::TextComponent>(vtextcomponent, rb_cCeguiTextComponent);
}
#endif /* __RubyCeguiTextComponent_H__ */
