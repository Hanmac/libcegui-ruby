/*
 * ceguistateimagery.cpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */


#include "ceguistateimagery.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::StateImagery*>(self)

VALUE rb_cCeguiStateImagery;
namespace CeguiStateImagery {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::StateImagery);
}

macro_attr(Name,CEGUI::String)
macro_attr_bool(ClippedToDisplay)

/*
 * call-seq:
 *   inspect -> String
 *
 * Human-readable description.
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(self,"name");
	return rb_f_sprintf(3,array);
}
/*
 *
 */
VALUE _each(VALUE self)
{
	wrap_each(_self->getLayerIterator());
	return self;
}

}

void Init_CeguiStateImagery(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiStateImagery,"name",1,1);
	rb_define_attr(rb_cCeguiStateImagery,"clippedToDisplay",1,1);

#endif
	using namespace CeguiStateImagery;

	rb_cCeguiStateImagery = rb_define_class_under(rb_mCegui,"StateImagery",rb_cObject);

	rb_define_alloc_func(rb_cCeguiStateImagery,_alloc);

	rb_define_attr_method(rb_cCeguiStateImagery,"name",_getName,_setName);
	rb_define_attr_method(rb_cCeguiStateImagery,"clippedToDisplay",_getClippedToDisplay,_setClippedToDisplay);


	rb_define_method(rb_cCeguiStateImagery,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiStateImagery,"each",RUBY_METHOD_FUNC(_each),0);

}



