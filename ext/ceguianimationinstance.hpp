/*
 * ceguianimationinstance.hpp
 *
 *  Created on: 21.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiAnimationInstance_H__
#define __RubyCeguiAnimationInstance_H__

#include "main.hpp"
#include "ceguiexception.hpp"
void Init_CeguiAnimationInstance(VALUE rb_mCegui);
extern VALUE rb_cCeguiAnimationInstance;

template <>
inline VALUE wrap< CEGUI::AnimationInstance >(CEGUI::AnimationInstance *instance )
{
	if(instance==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiAnimationInstance, NULL, NULL, instance);
}
template <>
inline CEGUI::AnimationInstance* wrap< CEGUI::AnimationInstance* >(const VALUE &vinstance)
{
	return unwrapPtr<CEGUI::AnimationInstance>(vinstance, rb_cCeguiAnimationInstance);
}
#endif /* __RubyCeguiAnimationInstance_H__ */
