/*
 * ceguiframecomponent.hpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiFrameComponent_H__
#define __RubyCeguiFrameComponent_H__

#include "main.hpp"
void Init_CeguiFrameComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiFrameComponent;


template <>
inline VALUE wrap< CEGUI::FrameComponent >(CEGUI::FrameComponent *framecomponent )
{
	return Data_Wrap_Struct(rb_cCeguiFrameComponent, NULL, NULL, framecomponent);
}

template <>
inline CEGUI::FrameComponent* wrap< CEGUI::FrameComponent* >(const VALUE &vframecomponent)
{
	return unwrapPtr<CEGUI::FrameComponent>(vframecomponent, rb_cCeguiFrameComponent);
}
#endif /* __RubyCeguiFrameComponent_H__ */
