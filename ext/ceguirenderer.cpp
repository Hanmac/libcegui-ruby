#include "ceguirenderer.hpp"

#define _self wrap<CEGUI::Renderer*>(self)
VALUE rb_cCeguiRenderer;

macro_attr(Renderer,DisplaySize,CEGUI::Size)
/*
*/
VALUE CeguiRenderer_getName(VALUE self)
{
	return wrap(_self->getIdentifierString());
}

/*
*/
VALUE CeguiRenderer_beginRendering(VALUE self)
{
	_self->beginRendering();
	return self;
}
/*
*/
VALUE CeguiRenderer_endRendering(VALUE self)
{
	_self->endRendering();
	return self;
}

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiRenderer_inspect(VALUE self)
{
	VALUE array[2];
	array[0]=rb_str_new2("#<%s>");
	array[1]=CeguiRenderer_getName(self);
	return rb_f_sprintf(2,array);
}

void Init_CeguiRenderer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiRenderer,"displaySize",1,1);
#endif
	rb_cCeguiRenderer = rb_define_class_under(rb_mCegui,"Renderer",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderer);
	
	rb_define_attr_method(rb_cCeguiRenderer,"displaySize",CeguiRenderer_getDisplaySize,CeguiRenderer_setDisplaySize);

	rb_define_method(rb_cCeguiRenderer,"inspect",RUBY_METHOD_FUNC(CeguiRenderer_inspect),0);
	rb_define_method(rb_cCeguiRenderer,"name",RUBY_METHOD_FUNC(CeguiRenderer_getName),0);

	rb_define_method(rb_cCeguiRenderer,"beginRendering",RUBY_METHOD_FUNC(CeguiRenderer_beginRendering),0);
	rb_define_method(rb_cCeguiRenderer,"endRendering",RUBY_METHOD_FUNC(CeguiRenderer_endRendering),0);

}
