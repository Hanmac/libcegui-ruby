#ifndef __RubyCeguiFont_H__
#define __RubyCeguiFont_H__

#include "ceguiresource.hpp"

void Init_CeguiFont(VALUE rb_mCegui);
extern VALUE rb_cCeguiFont;

template <>
inline VALUE wrap< CEGUI::Font >(CEGUI::Font *font )
{
	if(font==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiFont, NULL, NULL,
			new RubyResource(font->getName()));
}


template <>
inline CEGUI::Font* unwrapResource_impl<CEGUI::Font>(CEGUI::String name)
{
	return &CEGUI::FontManager::getSingletonPtr()->get(name);
}


template <>
inline CEGUI::Font* wrap< CEGUI::Font* >(const VALUE &vfont)
{
	return unwrapResource<CEGUI::Font>(vfont, rb_cCeguiFont);
}
#endif /* __RubyCeguiFont_H__ */
