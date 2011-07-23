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
#endif
#endif /* __RubyCeguiRenderer_H__ */
