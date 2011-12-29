#ifndef __RubyCeguiTextureTarget_H__
#define __RubyCeguiTextureTarget_H__

#include "main.hpp"
void Init_CeguiTextureTarget(VALUE rb_mCegui);
extern VALUE rb_cCeguiTextureTarget;


template <>
inline VALUE wrap< CEGUI::TextureTarget >(CEGUI::TextureTarget *target )
{
	if(target==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiTextureTarget, NULL, NULL, target);
}

template <>
inline CEGUI::TextureTarget* wrap< CEGUI::TextureTarget* >(const VALUE &vtarget)
{
	return unwrapPtr<CEGUI::TextureTarget>(vtarget, rb_cCeguiTextureTarget);
}
#endif /* __RubyCeguiTextureTarget_H__ */
