#include "ceguigeometrybuffer.hpp"
#include "ceguiexception.hpp"

#include "ceguitexture.hpp"
#include "ceguivertex.hpp"

#define _self wrap<CEGUI::GeometryBuffer*>(self)

VALUE rb_cCeguiGeometryBuffer;

macro_attr(GeometryBuffer,ActiveTexture,CEGUI::Texture*)
/*
*/
VALUE CeguiGeometryBuffer_draw(VALUE self)
{
	_self->draw();
	return self;
}
/*
*/
VALUE CeguiGeometryBuffer_reset(VALUE self)
{
	_self->reset();
	return self;
}
/*
*/
void Init_CeguiGeometryBuffer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiGeometryBuffer,"activeTexture",1,1);
#endif
	rb_cCeguiGeometryBuffer = rb_define_class_under(rb_mCegui,"GeometryBuffer",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiGeometryBuffer);
	
	rb_define_method(rb_cCeguiGeometryBuffer,"draw",RUBY_METHOD_FUNC(CeguiGeometryBuffer_draw),0);
	rb_define_method(rb_cCeguiGeometryBuffer,"reset",RUBY_METHOD_FUNC(CeguiGeometryBuffer_reset),0);
	
	rb_define_attr_method(rb_cCeguiGeometryBuffer,"activeTexture",CeguiGeometryBuffer_getActiveTexture,CeguiGeometryBuffer_setActiveTexture);
}
