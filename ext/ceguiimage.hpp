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
inline VALUE wrap<const CEGUI::Image >(const CEGUI::Image *image )
{
	return wrap(const_cast<CEGUI::Image*>(image));
}
template <>
inline CEGUI::Image* wrap< CEGUI::Image* >(const VALUE &vimage)
{
	if (rb_obj_is_kind_of(vimage, rb_cString)){
		return &CEGUI::ImageManager::getSingletonPtr()->get(wrap<CEGUI::String>(vimage));
	}else
		return unwrapPtr<CEGUI::Image>(vimage, rb_cCeguiImage);
}
#endif /* __RubyCeguiImage_H__ */
