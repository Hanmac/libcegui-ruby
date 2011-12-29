/*
 * ceguipropertyinitialiser.cpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */

#include "ceguipropertyinitialiser.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::PropertyInitialiser*>(self)

VALUE rb_cCeguiPropertyInitialiser;
namespace CeguiPropertyInitialiser {

macro_attr(TargetPropertyName,CEGUI::String)

macro_attr(InitialiserValue,CEGUI::String)

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::PropertyInitialiser);
}

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
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(self,"name");
	array[3]=rb_funcall(self,"value");
	return rb_f_sprintf(4,array);
}

}

void Init_CeguiPropertyInitialiser(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiPropertyInitialiser,"name",1,1);
	rb_define_attr(rb_cCeguiPropertyInitialiser,"value",1,1);
#endif
	using namespace CeguiPropertyInitialiser;

	rb_cCeguiPropertyInitialiser = rb_define_class_under(rb_mCegui,"PropertyInitialiser",rb_cObject);

	rb_define_alloc_func(rb_cCeguiPropertyInitialiser,_alloc);

	rb_define_attr_method(rb_cCeguiPropertyInitialiser,"name",_getTargetPropertyName,_setTargetPropertyName);

	rb_define_attr_method(rb_cCeguiPropertyInitialiser,"value",_getInitialiserValue,_setInitialiserValue);

	rb_define_method(rb_cCeguiPropertyInitialiser,"inspect",RUBY_METHOD_FUNC(_inspect),0);

}
