#ifndef __RubyCeguiNullRenderer_H__
#define __RubyCeguiNullRenderer_H__

#include "main.hpp"

void Init_CeguiNullRenderer(VALUE rb_mCegui);
extern VALUE rb_cCeguiNullRenderer;

#if HAVE_RENDERERMODULES_NULL_CEGUINULLRENDERER_H
#include <RendererModules/Null/CEGUINullRenderer.h>
template <>
inline VALUE wrap< CEGUI::NullRenderer >(CEGUI::NullRenderer *renderer )
{
	if(renderer==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiNullRenderer, NULL, NULL, renderer);
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
