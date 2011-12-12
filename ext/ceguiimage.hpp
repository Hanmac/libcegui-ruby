#ifndef __RubyCeguiImage_H__
#define __RubyCeguiImage_H__

#include "main.hpp"
void Init_CeguiImage(VALUE rb_mCegui);
extern VALUE rb_cCeguiImage;

template <>
inline VALUE wrap< CEGUI::Image >(CEGUI::Image *image )
{
	if(image==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiImage, NULL, NULL, image);
}
template <>
inline CEGUI::Image* wrap< CEGUI::Image* >(const VALUE &vimage)
{
	if (rb_obj_is_kind_of(vimage, rb_cCeguiImage)){
		CEGUI::Image *image;
		Data_Get_Struct( vimage, CEGUI::Image, image);
		return image;
	}else if (rb_obj_is_kind_of(vimage, rb_cString)){
		return &CEGUI::ImageManager::getSingletonPtr()->get(wrap<CEGUI::String>(vimage));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiImage),rb_obj_classname(vimage));
		return NULL;
	}
}
#endif /* __RubyCeguiImage_H__ */
