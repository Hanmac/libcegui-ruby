#ifndef __RubyCeguiAnimation_H__
#define __RubyCeguiAnimation_H__

#include "ceguiresource.hpp"

void Init_CeguiAnimation(VALUE rb_mCegui);
extern VALUE rb_cCeguiAnimation;

template <>
inline VALUE wrap< CEGUI::Animation >(CEGUI::Animation *animation )
{
	if(animation==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiAnimation, NULL, NULL,
			new RubyResource(animation->getName()));
}

template <>
inline CEGUI::Animation* unwrapResource_impl<CEGUI::Animation>(CEGUI::String name)
{
	return CEGUI::AnimationManager::getSingletonPtr()->getAnimation(name);
}

template <>
inline CEGUI::Animation* wrap< CEGUI::Animation* >(const VALUE &vanimation)
{
	return unwrapResource<CEGUI::Animation>(vanimation, rb_cCeguiAnimation);
}
#endif /* __RubyCeguiAnimation_H__ */
