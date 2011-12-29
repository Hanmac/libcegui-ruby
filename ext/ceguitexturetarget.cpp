#include "ceguirendertarget.hpp"
#include "ceguitexturetarget.hpp"
#include "ceguiexception.hpp"

VALUE rb_cCeguiTextureTarget;

#define _self wrap<CEGUI::TextureTarget*>(self)

namespace CeguiTextureTarget
{
	singlefunc(clear)
	singlereturn(isRenderingInverted)

}

void Init_CeguiTextureTarget(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiRenderTarget = rb_define_class_under(rb_mCegui,"RenderTarget",rb_cObject);
#endif
	using namespace CeguiTextureTarget;
	rb_cCeguiTextureTarget = rb_define_class_under(rb_mCegui,"TextureTarget",rb_cCeguiRenderTarget);

}
