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
	if (rb_obj_is_kind_of(vframecomponent, rb_cCeguiFrameComponent)){
		CEGUI::FrameComponent *framecomponent;
		Data_Get_Struct( vframecomponent, CEGUI::FrameComponent, framecomponent);
		return framecomponent;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiFrameComponent),rb_obj_classname(vframecomponent));
		return NULL;
	}
}
#endif /* __RubyCeguiFrameComponent_H__ */
