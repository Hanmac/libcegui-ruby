#ifndef __RubyCeguiFont_H__
#define __RubyCeguiFont_H__

#include "main.hpp"
#include "ceguiexception.hpp"
void Init_CeguiFont(VALUE rb_mCegui);
extern VALUE rb_cCeguiFont;

template <>
inline VALUE wrap< CEGUI::Font >(CEGUI::Font *font )
{
	if(font==NULL)
		return Qnil;
	RubyResource *temp = new RubyResource;
	temp->name = font->getName();
	return Data_Wrap_Struct(rb_cCeguiFont, NULL, NULL, temp);
}
template <>
inline CEGUI::Font* wrap< CEGUI::Font* >(const VALUE &vfont)
{
	try {
		if (rb_obj_is_kind_of(vfont, rb_cString)){
			return &CEGUI::FontManager::getSingletonPtr()->get(wrap<CEGUI::String>(vfont));
		}else	if (rb_obj_is_kind_of(vfont, rb_cCeguiFont)){
			RubyResource *font;
			Data_Get_Struct( vfont, RubyResource, font);
			return &CEGUI::FontManager::getSingletonPtr()->get(font->name);
		}else{
			rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiFont),rb_obj_classname(vfont));
			return NULL;
		}
	}catch(CEGUI::Exception& e){
		rb_raise(e);
		return NULL;
	}
}
#endif /* __RubyCeguiFont_H__ */
