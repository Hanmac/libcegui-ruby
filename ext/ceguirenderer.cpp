#include "ceguirenderer.hpp"

#include "ceguisize.hpp"
#include "ceguitexture.hpp"
#include "ceguitexturetarget.hpp"
#include "ceguigeometrybuffer.hpp"

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
*/
VALUE CeguiRenderer_createGeometryBuffer(VALUE self)
{
	return wrap(_self->createGeometryBuffer());
}

/*
*/
VALUE CeguiRenderer_createTextureTarget(VALUE self)
{
	return wrap(_self->createTextureTarget());
}

/*
*/
VALUE CeguiRenderer_createTexture(int argc,VALUE *argv,VALUE self)
{
	VALUE obj,resource_group;
	rb_scan_args(argc, argv, "02",&obj,&resource_group);
	if(argc==0)
		return wrap(_self->createTexture());
	else if(argc==1)
		return wrap(_self->createTexture(wrap<CEGUI::Size>(obj)));
	else
		return wrap(_self->createTexture(wrap<CEGUI::String>(obj),wrap<CEGUI::String>(resource_group)));
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

	rb_define_method(rb_cCeguiRenderer,"createGeometryBuffer",RUBY_METHOD_FUNC(CeguiRenderer_createGeometryBuffer),0);
	rb_define_method(rb_cCeguiRenderer,"createTexture",RUBY_METHOD_FUNC(CeguiRenderer_createTexture),-1);
	rb_define_method(rb_cCeguiRenderer,"createTextureTarget",RUBY_METHOD_FUNC(CeguiRenderer_createTextureTarget),0);

}
