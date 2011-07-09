#include "ceguirenderer.hpp"
#include "ceguiopenglrenderer.hpp"

VALUE rb_cCeguiOpenGLRenderer;
#if HAVE_RENDERERMODULES_OPENGL_CEGUIOPENGLRENDERER_H
/*
*/
VALUE CeguiOpenGLRenderer_bootstrap(VALUE self)
{
	return wrap(CEGUI::OpenGLRenderer::bootstrapSystem());
}
/*
*/
VALUE CeguiOpenGLRenderer_create(VALUE self)
{
	return wrap(CEGUI::OpenGLRenderer::create());
}
#endif
void Init_CeguiOpenGLRenderer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiRenderer = rb_define_class_under(rb_mCegui,"Renderer",rb_cObject);	
#endif
#if HAVE_RENDERERMODULES_OPENGL_CEGUIOPENGLRENDERER_H
	rb_cCeguiOpenGLRenderer = rb_define_class_under(rb_mCegui,"OpenGLRenderer",rb_cCeguiRenderer);
	
	rb_define_singleton_method(rb_cCeguiOpenGLRenderer,"bootstrap",RUBY_METHOD_FUNC(CeguiOpenGLRenderer_bootstrap),0);
	rb_define_singleton_method(rb_cCeguiOpenGLRenderer,"create",RUBY_METHOD_FUNC(CeguiOpenGLRenderer_create),0);
#endif
}
