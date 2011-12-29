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
	return unwrapPtr<CEGUI::RenderingSurface>(vsurface, rb_cCeguiRenderingSurface);
}
#endif /* __RubyCeguiRenderingSurface_H__ */
