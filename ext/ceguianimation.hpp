#ifndef __RubyCeguiAnimation_H__
#define __RubyCeguiAnimation_H__

#include "main.hpp"
#include "ceguiexception.hpp"
void Init_CeguiAnimation(VALUE rb_mCegui);
extern VALUE rb_cCeguiAnimation;

template <>
inline VALUE wrap< CEGUI::Animation >(CEGUI::Animation *animation )
{
	if(animation==NULL)
		return Qnil;
	RubyResource *temp = new RubyResource;
	temp->name = animation->getName();
	return Data_Wrap_Struct(rb_cCeguiAnimation, NULL, NULL, temp);
}
template <>
inline CEGUI::Animation* wrap< CEGUI::Animation* >(const VALUE &vanimation)
{
	try {
		if (rb_obj_is_kind_of(vanimation, rb_cString)){
			return CEGUI::AnimationManager::getSingletonPtr()->getAnimation(wrap<CEGUI::String>(vanimation));
		}else	if (rb_obj_is_kind_of(vanimation, rb_cCeguiAnimation)){
			RubyResource *animation;
			Data_Get_Struct( vanimation, RubyResource, animation);
			return CEGUI::AnimationManager::getSingletonPtr()->getAnimation(animation->name);
		}else{
			rb_raise(rb_eTypeError,"Excepted %s got %s!",
				rb_class2name(rb_cCeguiAnimation),rb_obj_classname(vanimation));
			return NULL;
		}
	}catch(CEGUI::Exception& e){
		rb_raise(e);
		return NULL;
	}
}
#endif /* __RubyCeguiAnimation_H__ */
