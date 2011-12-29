#include "ceguibuttonbase.hpp"

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::ButtonBase*>(self)
VALUE rb_cCeguiButtonBase;

namespace CeguiButtonBase {

singlereturn(isPushed)
singlereturn(isHovering)

}
/* Document-method: pushed?
*/
/* Document-method: hovering?
*/
/*
*/
void Init_CeguiButtonBase(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

#endif
	using namespace CeguiButtonBase;

	rb_cCeguiButtonBase = rb_define_class_under(rb_mCegui,"ButtonBase",rb_cCeguiWindow);
	
	rb_define_method(rb_cCeguiButtonBase,"pushed?",RUBY_METHOD_FUNC(_isPushed),0);
	rb_define_method(rb_cCeguiButtonBase,"hovering?",RUBY_METHOD_FUNC(_isHovering),0);
}
