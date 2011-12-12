/*
 * ceguiaffector.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#define _self wrap<CEGUI::Affector*>(self)

#include "ceguiaffector.hpp"
#include "ceguiexception.hpp"

VALUE rb_cCeguiAffector;
namespace CeguiAffector {

macro_attr(TargetProperty,CEGUI::String)


}
/*
 *
 */
void Init_CeguiAffector(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");


	rb_define_attr(rb_cCeguiAffector,"duration",1,1);
	rb_define_attr(rb_cCeguiAffector,"autostart",1,1);
#endif
	using namespace CeguiAffector;

	rb_cCeguiAffector = rb_define_class_under(rb_mCegui,"Affector",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiAffector);

//rb_define_method(rb_cCeguiAffector,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cCeguiAffector,rb_mEnumerable);

rb_define_attr_method(rb_cCeguiAffector,"targetProperty",_getTargetProperty,_setTargetProperty);


}
