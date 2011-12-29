#include "ceguirendertarget.hpp"
#include "ceguiexception.hpp"
#include "ceguirect.hpp"
VALUE rb_cCeguiRenderTarget;

#define _self wrap<CEGUI::RenderTarget*>(self)

namespace CeguiRenderTarget {
macro_attr(Area,CEGUI::Rectf)

singlefunc(activate)
singlefunc(deactivate)
}

void Init_CeguiRenderTarget(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiRenderTarget,"area",1,1);
#endif
	using namespace CeguiRenderTarget;

	rb_cCeguiRenderTarget = rb_define_class_under(rb_mCegui,"RenderTarget",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderTarget);
	
	rb_define_attr_method(rb_cCeguiRenderTarget,"area",_getArea,_setArea);

	rb_define_method(rb_cCeguiRenderTarget,"activate",RUBY_METHOD_FUNC(_activate),0);
	rb_define_method(rb_cCeguiRenderTarget,"deactivate",RUBY_METHOD_FUNC(_deactivate),0);

}
