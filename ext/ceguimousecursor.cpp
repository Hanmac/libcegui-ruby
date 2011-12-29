/*
 * ceguimousecursor.cpp
 *
 *  Created on: 21.12.2011
 *      Author: hanmac
 */

#include "ceguimousecursor.hpp"
#include "ceguiimage.hpp"
#include "ceguivector2.hpp"
#include "ceguirect.hpp"
#include "ceguiurect.hpp"
#include "ceguisize.hpp"
#include "ceguieventset.hpp"

#define _self wrap< CEGUI::MouseCursor* >(rb_mCeguiMouseCursor)

VALUE rb_mCeguiMouseCursor;

namespace CeguiMouseCursor{

macro_attr(Image,CEGUI::Image*)
macro_attr(Position,CEGUI::Vector2f)
macro_attr(ConstraintArea,CEGUI::Rectf*)

macro_attr(UnifiedConstraintArea,CEGUI::URect*)
macro_attr_bool(Visible)
macro_attr(ExplicitRenderSize,CEGUI::Sizef)

singlefunc(hide)
singlefunc(show)

singlefunc(draw)

}

/* Document-method: image

*/
/* Document-method: position

*/
/* Document-method: constraintArea

*/
/* Document-method: unifiedConstraintArea

*/
/* Document-method: visible

*/
/* Document-method: explicitRenderSize

*/

/* Document-method: image=

*/
/* Document-method: position=

*/
/* Document-method: constraintArea=

*/
/* Document-method: unifiedConstraintArea=

*/
/* Document-method: visible=

*/
/* Document-method: explicitRenderSize=

*/

/* Document-method: hide

*/
/* Document-method: show

*/
/* Document-method: draw

*/

void Init_CeguiMouseCursor(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif

	using namespace CeguiMouseCursor;

	rb_mCeguiMouseCursor = rb_define_module_under(rb_mCegui,"MouseCursor");

	rb_extend_object(rb_mCeguiSystem,rb_mCeguiEventSet);

	rb_define_module_function(rb_mCeguiMouseCursor,"image",RUBY_METHOD_FUNC(_getImage),0);
	rb_define_module_function(rb_mCeguiMouseCursor,"position",RUBY_METHOD_FUNC(_getPosition),0);
	rb_define_module_function(rb_mCeguiMouseCursor,"constraintArea",RUBY_METHOD_FUNC(_getConstraintArea),0);

	rb_define_module_function(rb_mCeguiMouseCursor,"unifiedConstraintArea",RUBY_METHOD_FUNC(_getUnifiedConstraintArea),0);
	rb_define_module_function(rb_mCeguiMouseCursor,"visible",RUBY_METHOD_FUNC(_getVisible),0);
	rb_define_module_function(rb_mCeguiMouseCursor,"explicitRenderSize",RUBY_METHOD_FUNC(_getExplicitRenderSize),0);

	rb_define_module_function(rb_mCeguiMouseCursor,"image=",RUBY_METHOD_FUNC(_setImage),1);
	rb_define_module_function(rb_mCeguiMouseCursor,"position=",RUBY_METHOD_FUNC(_setPosition),1);
	rb_define_module_function(rb_mCeguiMouseCursor,"constraintArea=",RUBY_METHOD_FUNC(_setConstraintArea),1);

	rb_define_module_function(rb_mCeguiMouseCursor,"unifiedConstraintArea=",RUBY_METHOD_FUNC(_setUnifiedConstraintArea),1);
	rb_define_module_function(rb_mCeguiMouseCursor,"visible=",RUBY_METHOD_FUNC(_setVisible),1);
	rb_define_module_function(rb_mCeguiMouseCursor,"explicitRenderSize=",RUBY_METHOD_FUNC(_setExplicitRenderSize),1);

	rb_define_module_function(rb_mCeguiMouseCursor,"hide",RUBY_METHOD_FUNC(_hide),0);
	rb_define_module_function(rb_mCeguiMouseCursor,"show",RUBY_METHOD_FUNC(_show),0);

	rb_define_module_function(rb_mCeguiMouseCursor,"draw",RUBY_METHOD_FUNC(_draw),0);

	rb_define_const(rb_mCeguiMouseCursor,"EventNamespace",wrap(CEGUI::MouseCursor::EventNamespace));
	rb_define_const(rb_mCeguiMouseCursor,"EventImageChanged",wrap(CEGUI::MouseCursor::EventImageChanged));

}
