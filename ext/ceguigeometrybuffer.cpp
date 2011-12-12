#include "ceguigeometrybuffer.hpp"
#include "ceguiexception.hpp"

#include "ceguitexture.hpp"
#include "ceguivertex.hpp"

#define _self wrap<CEGUI::GeometryBuffer*>(self)

VALUE rb_cCeguiGeometryBuffer;
namespace CeguiGeometryBuffer {

macro_attr(ActiveTexture,CEGUI::Texture*)

singlefunc(draw)
singlefunc(reset)

}

/* Document-method: draw

*/
/* Document-method: reset

*/

/*
*/
void Init_CeguiGeometryBuffer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiGeometryBuffer,"activeTexture",1,1);
#endif
	using namespace CeguiGeometryBuffer;

	rb_cCeguiGeometryBuffer = rb_define_class_under(rb_mCegui,"GeometryBuffer",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiGeometryBuffer);
	
	rb_define_method(rb_cCeguiGeometryBuffer,"draw",RUBY_METHOD_FUNC(_draw),0);
	rb_define_method(rb_cCeguiGeometryBuffer,"reset",RUBY_METHOD_FUNC(_reset),0);
	
	rb_define_attr_method(rb_cCeguiGeometryBuffer,"activeTexture",_getActiveTexture,_setActiveTexture);
}
