/*
 * ceguinamedarea.cpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */

#include "ceguinamedarea.hpp"
#include "ceguicomponentarea.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::NamedArea*>(self)

VALUE rb_cCeguiNamedArea;
namespace CeguiNamedArea {

macro_attr(Area,CEGUI::ComponentArea)

macro_attr(Name,CEGUI::String)

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::NamedArea);
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
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(self,"name");
	return rb_f_sprintf(3,array);
}

}

void Init_CeguiNamedArea(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiNamedArea,"name",1,1);
	rb_define_attr(rb_cCeguiNamedArea,"area",1,1);
#endif
	using namespace CeguiNamedArea;

	rb_cCeguiNamedArea = rb_define_class_under(rb_mCegui,"NamedArea",rb_cObject);

	rb_define_alloc_func(rb_cCeguiNamedArea,_alloc);

	rb_define_attr_method(rb_cCeguiNamedArea,"area",_getArea,_setArea);

	rb_define_attr_method(rb_cCeguiNamedArea,"name",_getName,_setName);

	rb_define_method(rb_cCeguiNamedArea,"inspect",RUBY_METHOD_FUNC(_inspect),0);

}





