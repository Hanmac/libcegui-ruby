/*
 * ceguilayerspecification.cpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */

#include "ceguilayerspecification.hpp"
#include "ceguisectionspecification.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::LayerSpecification*>(self)

VALUE rb_cCeguiLayerSpecification;
namespace CeguiLayerSpecification {

macro_attr(LayerPriority,uint)



VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::LayerSpecification);
}

/*
 *
 */
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getSectionIterator());
	return self;
}


}

void Init_CeguiLayerSpecification(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiLayerSpecification,"priority",1,1);

#endif
	using namespace CeguiLayerSpecification;

	rb_cCeguiLayerSpecification = rb_define_class_under(rb_mCegui,"LayerSpecification",rb_cObject);
	rb_define_alloc_func(rb_cCeguiLayerSpecification,_alloc);

	rb_include_module(rb_cCeguiLayerSpecification,rb_mEnumerable);
	rb_define_method(rb_cCeguiLayerSpecification,"each",RUBY_METHOD_FUNC(_each),0);

	rb_define_attr_method(rb_cCeguiLayerSpecification,"priority",_getLayerPriority,_setLayerPriority);


}





