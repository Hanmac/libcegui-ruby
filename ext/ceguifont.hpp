#ifndef __RubyCeguiFont_H__
#define __RubyCeguiFont_H__

#include "main.hpp"
void Init_CeguiFont(VALUE rb_mCegui);
extern VALUE rb_cCeguiFont;


template <>
inline VALUE wrap< CEGUI::Font >(CEGUI::Font *font )
{
	if(font==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiFont, NULL, NULL, font);
}
template <>
inline CEGUI::Font* wrap< CEGUI::Font* >(const VALUE &vfont)
{
	if (rb_obj_is_kind_of(vfont, rb_cString)){
		return &CEGUI::FontManager::getSingletonPtr()->get(wrap<CEGUI::String>(vfont));
	}else	if (rb_obj_is_kind_of(vfont, rb_cCeguiFont)){
		CEGUI::Font *font;
		Data_Get_Struct( vfont, CEGUI::Font, font);
		return font;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiFont),rb_obj_classname(vfont));
		return NULL;
	}
}
#endif /* __RubyCeguiFont_H__ */
