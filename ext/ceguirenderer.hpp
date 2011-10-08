#ifndef __RubyCeguiRenderer_H__
#define __RubyCeguiRenderer_H__

#include "main.hpp"
void Init_CeguiRenderer(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderer;
extern VALUE rb_cCeguiNullRenderer;
extern VALUE rb_cCeguiOpenGLRenderer;

#if HAVE_RENDERERMODULES_NULL_RENDERER_H
#include <RendererModules/Null/Renderer.h>
template <>
inline VALUE wrap< CEGUI::NullRenderer >(CEGUI::NullRenderer *renderer )
{
	if(renderer==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiNullRenderer, NULL, NULL, renderer);
}
#endif

#if HAVE_RENDERERMODULES_OPENGL_RENDERER_H
#include <RendererModules/OpenGL/Renderer.h>
template <>
inline VALUE wrap< CEGUI::OpenGLRenderer >(CEGUI::OpenGLRenderer *renderer )
{
	if(renderer==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiOpenGLRenderer, NULL, NULL, renderer);
}
#endif


template <>
inline VALUE wrap< CEGUI::Renderer >(CEGUI::Renderer *renderer )
{
	if(renderer==NULL)
		return Qnil;
#if HAVE_RENDERERMODULES_NULL_RENDERER_H
	CEGUI::NullRenderer *nullrenderer = dynamic_cast<CEGUI::NullRenderer*>(renderer);
	if(nullrenderer)
		return wrap(nullrenderer);
#endif
#if HAVE_RENDERERMODULES_OPENGL_RENDERER_H
	CEGUI::OpenGLRenderer *openglrenderer = dynamic_cast<CEGUI::OpenGLRenderer*>(renderer);
	if(openglrenderer)
		return wrap(openglrenderer);
#endif
	return Data_Wrap_Struct(rb_cCeguiRenderer, NULL, NULL, renderer);
}

template <>
inline CEGUI::Renderer* wrap< CEGUI::Renderer* >(const VALUE &vrenderer)
{
	if (rb_obj_is_kind_of(vrenderer, rb_cCeguiRenderer)){
		CEGUI::Renderer *renderer;
		Data_Get_Struct( vrenderer, CEGUI::Renderer, renderer);
		return renderer;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiRenderer),rb_obj_classname(vrenderer));
		return NULL;
	}
}
#endif /* __RubyCeguiRenderer_H__ */
