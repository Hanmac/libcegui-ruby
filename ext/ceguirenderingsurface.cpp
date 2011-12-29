#include "ceguirenderingsurface.hpp"
#include "ceguiexception.hpp"
#include "ceguieventset.hpp"

VALUE rb_cCeguiRenderingSurface;

#define _self wrap<CEGUI::RenderingSurface*>(self)
namespace CeguiRenderingSurface
{
	singlefunc(draw)
	singlefunc(invalidate)
	singlefunc(clearGeometry)

}

void Init_CeguiRenderingSurface(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif
	using namespace CeguiRenderingSurface;

	rb_cCeguiRenderingSurface = rb_define_class_under(rb_mCegui,"RenderingSurface",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderingSurface);

	rb_include_module(rb_cCeguiRenderingSurface,rb_mCeguiEventSet);

	rb_define_method(rb_cCeguiRenderingSurface,"draw",RUBY_METHOD_FUNC(_draw),0);
	rb_define_method(rb_cCeguiRenderingSurface,"invalidate",RUBY_METHOD_FUNC(_invalidate),0);
	rb_define_method(rb_cCeguiRenderingSurface,"clear",RUBY_METHOD_FUNC(_clearGeometry),0);
}
