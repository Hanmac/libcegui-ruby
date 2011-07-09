#ifndef __RubyCeguiOpenGLRenderer_H__
#define __RubyCeguiOpenGLRenderer_H__

#include "main.hpp"

void Init_CeguiOpenGLRenderer(VALUE rb_mCegui);
extern VALUE rb_cCeguiOpenGLRenderer;

#if HAVE_RENDERERMODULES_OPENGL_CEGUIOPENGLRENDERER_H
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
template <>
inline VALUE wrap< CEGUI::OpenGLRenderer >(CEGUI::OpenGLRenderer *renderer )
{
	if(renderer==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiOpenGLRenderer, NULL, NULL, renderer);
}

//template <>
//inline CEGUI::Renderer* wrap< CEGUI::Renderer* >(const VALUE &vrenderer)
//{
//	if (rb_obj_is_kind_of(vrenderer, rb_cCeguiRenderer)){
//		CEGUI::Renderer *renderer;
//		Data_Get_Struct( vrenderer, CEGUI::Renderer, renderer);
//		return renderer;
//	}else{
//		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiRenderer),rb_obj_classname(vrenderer));
//		return NULL;
//	}
//}
#endif
#endif /* __RubyCeguiRenderer_H__ */
