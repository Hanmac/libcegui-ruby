/*
 * ceguikeyframe.hpp
 *
 *  Created on: 21.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiKeyFrame_H__
#define __RubyCeguiKeyFrame_H__

#include "main.hpp"
#include "ceguiexception.hpp"
void Init_CeguiKeyFrame(VALUE rb_mCegui);
extern VALUE rb_cCeguiKeyFrame;

template <>
inline VALUE wrap< CEGUI::KeyFrame >(CEGUI::KeyFrame *keyframe )
{
	if(keyframe==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiKeyFrame, NULL, NULL, keyframe);
}
template <>
inline CEGUI::KeyFrame* wrap< CEGUI::KeyFrame* >(const VALUE &vkeyframe)
{
	return unwrapPtr<CEGUI::KeyFrame>(vkeyframe, rb_cCeguiKeyFrame);
}
#endif /* __RubyCeguiKeyFrame_H__ */
