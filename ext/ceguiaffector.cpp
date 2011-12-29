/*
 * ceguiaffector.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#define _self wrap<CEGUI::Affector*>(self)

#include "ceguiaffector.hpp"
#include "ceguikeyframe.hpp"
#include "ceguiexception.hpp"

VALUE rb_cCeguiAffector;
namespace CeguiAffector {

macro_attr(TargetProperty,CEGUI::String)
macro_attr(Interpolator,CEGUI::Interpolator*)
macro_attr(ApplicationMethod,CEGUI::Affector::ApplicationMethod)

VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for(uint i = 0;i > _self->getNumKeyFrames();++i)
	{
		CEGUI::KeyFrame* frame = _self->getKeyFrameAtIdx(i);
		rb_yield_values(2,DBL2NUM(frame->getPosition()),wrap(frame));
	}
	return self;
}

VALUE _createKeyFrame(VALUE self,VALUE position)
{
	return wrap(_self->createKeyFrame(NUM2DBL(position)));
}

}
/*
 *
 */
void Init_CeguiAffector(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");


	rb_define_attr(rb_cCeguiAffector,"targetProperty",1,1);
	rb_define_attr(rb_cCeguiAffector,"interpolator",1,1);
	rb_define_attr(rb_cCeguiAffector,"applicationMethod",1,1);
#endif
	using namespace CeguiAffector;

	rb_cCeguiAffector = rb_define_class_under(rb_mCegui,"Affector",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiAffector);

	rb_define_method(rb_cCeguiAffector,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cCeguiAffector,rb_mEnumerable);

	rb_define_attr_method(rb_cCeguiAffector,"targetProperty",_getTargetProperty,_setTargetProperty);
	rb_define_attr_method(rb_cCeguiAffector,"interpolator",_getInterpolator,_setInterpolator);

	rb_define_attr_method(rb_cCeguiAffector,"applicationMethod",_getApplicationMethod,_setApplicationMethod);

	rb_define_method(rb_cCeguiAffector,"createKeyFrame",RUBY_METHOD_FUNC(_createKeyFrame),1);

}
