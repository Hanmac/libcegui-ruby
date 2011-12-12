#ifndef __RubyCeguiRenderingSurface_H__
#define __RubyCeguiRenderingSurface_H__

#include "main.hpp"
void Init_CeguiRenderingSurface(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderingSurface;


template <>
inline VALUE wrap< CEGUI::RenderingSurface >(CEGUI::RenderingSurface *surface )
{
	if(surface==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiRenderingSurface, NULL, NULL, surface);
}

template <>
inline CEGUI::RenderingSurface* wrap< CEGUI::RenderingSurface* >(const VALUE &vsurface)
{
	if (rb_obj_is_kind_of(vsurface, rb_cCeguiRenderingSurface)){
		CEGUI::RenderingSurface *surface;
		Data_Get_Struct( vsurface, CEGUI::RenderingSurface, surface);
		return surface;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiRenderingSurface),rb_obj_classname(vsurface));
		return NULL;
	}
}
#endif /* __RubyCeguiRenderingSurface_H__ */
