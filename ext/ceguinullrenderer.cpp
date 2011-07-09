#include "ceguirenderer.hpp"
#include "ceguinullrenderer.hpp"

VALUE rb_cCeguiNullRenderer;
#if HAVE_RENDERERMODULES_NULL_CEGUINULLRENDERER_H
/*
*/
VALUE CeguiNullRenderer_bootstrap(VALUE self)
{
	return wrap(CEGUI::NullRenderer::bootstrapSystem());
}
/*
*/
VALUE CeguiNullRenderer_create(VALUE self)
{
	return wrap(CEGUI::NullRenderer::create());
}
#endif
void Init_CeguiNullRenderer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiRenderer = rb_define_class_under(rb_mCegui,"Renderer",rb_cObject);	
#endif
#if HAVE_RENDERERMODULES_NULL_CEGUINULLRENDERER_H
	rb_cCeguiNullRenderer = rb_define_class_under(rb_mCegui,"NullRenderer",rb_cCeguiRenderer);
	
	rb_define_singleton_method(rb_cCeguiNullRenderer,"bootstrap",RUBY_METHOD_FUNC(CeguiNullRenderer_bootstrap),0);
	rb_define_singleton_method(rb_cCeguiNullRenderer,"create",RUBY_METHOD_FUNC(CeguiNullRenderer_create),0);
#endif
}
