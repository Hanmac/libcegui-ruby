#ifndef __RubyCeguiTexture_H__
#define __RubyCeguiTexture_H__

#include "main.hpp"
void Init_CeguiTexture(VALUE rb_mCegui);
extern VALUE rb_cCeguiTexture;

template <>
inline VALUE wrap< CEGUI::Texture >(CEGUI::Texture *texture )
{
	if(texture==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiTexture, NULL, NULL, texture);
}

template <>
inline VALUE wrap< CEGUI::Texture >(const CEGUI::Texture &texture )
{
	return wrap(&texture);
}
template <>
inline CEGUI::Texture* wrap< CEGUI::Texture* >(const VALUE &vtexture)
{
	return unwrapPtr<CEGUI::Texture>(vtexture, rb_cCeguiTexture);
}
#endif /* __RubyCeguiTexture_H__ */
