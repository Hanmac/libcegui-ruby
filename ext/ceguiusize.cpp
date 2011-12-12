/*
 * ceguiusize.cpp
 *
 *  Created on: 06.12.2011
 *      Author: hanmac
 */
#include "ceguiusize.hpp"
#include "ceguiudim.hpp"
#define _self wrap<CEGUI::USize*>(self)
VALUE rb_cCeguiUSize;

namespace CeguiUSize {

macro_attr_prop(d_width,CEGUI::UDim)
macro_attr_prop(d_height,CEGUI::UDim)


VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::USize);
}
/*
*/
VALUE _initialize(VALUE self,VALUE x,VALUE y)
{
	_set_d_width(self,x);
	_set_d_height(self,y);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_d_width(self,_get_d_width(other));
	_set_d_height(self,_get_d_height(other));
	return result;
}
/*
 * call-seq:
 *   Size.inspect -> String
 *
 * Human-readable description.
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_d_width(self);
	array[3]=_get_d_height(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
/*
	CEGUI::USize* cother = wrap<CEGUI::USize*>(other);
	std::swap(_self->d_width,cother->d_width);
	std::swap(_self->d_height,cother->d_height);
*/
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::USize>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * wrap<CEGUI::UDim>(other));
}
/*
 * call-seq:
 *   vector.hash -> Integer
 *
 * hash from the combined Size values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_width(self));
	rb_ary_push(result,_get_d_height(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 *
 * packs a Size into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_width(self));
	rb_ary_push(result,_get_d_height(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 *
 * loads a string into an Size.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	_set_d_height(self,rb_ary_pop(result));
	_set_d_width(self,rb_ary_pop(result));
	return self;
}

}
/*
 * Document-class: CEGUI::USize
 *
 * This class represents an USize
*/
/* Document-attr: width
 * the width size */
/* Document-attr: height
 * the height size */
void Init_CeguiUSize(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiUSize,"width",1,1);
	rb_define_attr(rb_cCeguiUSize,"height",1,1);
#endif
	using namespace CeguiUSize;

	rb_cCeguiUSize = rb_define_class_under(rb_mCegui,"USize",rb_cObject);
	rb_define_alloc_func(rb_cCeguiUSize,_alloc);
	rb_define_method(rb_cCeguiUSize,"initialize",RUBY_METHOD_FUNC(_initialize),2);
	rb_define_private_method(rb_cCeguiUSize,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cCeguiUSize,"width",_get_d_width,_set_d_width);
	rb_define_attr_method(rb_cCeguiUSize,"height",_get_d_height,_set_d_height);

	rb_define_method(rb_cCeguiUSize,"inspect",RUBY_METHOD_FUNC(_inspect),0);
//	rb_define_method(rb_cCeguiUSize,"-@",RUBY_METHOD_FUNC(_minusself),0);

	rb_define_method(rb_cCeguiUSize,"+",RUBY_METHOD_FUNC(_plus),1);
//	rb_define_method(rb_cCeguiUSize,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiUSize,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cCeguiUSize,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiUSize,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiUSize,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiUSize,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}




