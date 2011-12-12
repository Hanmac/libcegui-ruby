/*
 * ceguiquaternion.cpp
 *
 *  Created on: 01.12.2011
 *      Author: hanmac
 */

#include "ceguiquaternion.hpp"
#define _self wrap<CEGUI::Quaternion*>(self)
VALUE rb_cCeguiQuaternion;

namespace CeguiQuaternion {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::Quaternion);
}
macro_attr_prop(d_w,float)
macro_attr_prop(d_x,float)
macro_attr_prop(d_y,float)
macro_attr_prop(d_z,float)
/*
*/
VALUE _initialize(VALUE self,VALUE w,VALUE x,VALUE y,VALUE z)
{
	_set_d_w(self,w);
	_set_d_x(self,x);
	_set_d_y(self,y);
	_set_d_z(self,z);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_d_w(self,_get_d_w(other));
	_set_d_x(self,_get_d_x(other));
	_set_d_y(self,_get_d_y(other));
	_set_d_z(self,_get_d_z(other));
	return result;
}
/*
 * call-seq:
 *   vector2.inspect -> String
 *
 * Human-readable description.
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_d_w(self);
	array[3]=_get_d_x(self);
	array[4]=_get_d_y(self);
	array[5]=_get_d_z(self);
	return rb_f_sprintf(6,array);
}
/*
*/
VALUE _minusself(VALUE self)
{
	return wrap(- *_self);
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::Quaternion* cother = wrap<CEGUI::Quaternion*>(other);
	std::swap(_self->d_w,cother->d_w);
	std::swap(_self->d_x,cother->d_x);
	std::swap(_self->d_y,cother->d_y);
	std::swap(_self->d_z,cother->d_z);
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Quaternion>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self + (-wrap<CEGUI::Quaternion>(other)));
}


/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * NUM2DBL(other));
}
/*
 * call-seq:
 *   hash -> Integer
 *
 * hash from the combined quaternion values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_w(self));
	rb_ary_push(result,_get_d_x(self));
	rb_ary_push(result,_get_d_y(self));
	rb_ary_push(result,_get_d_z(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 *
 * packs a Quaternion into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_w(self));
	rb_ary_push(result,_get_d_x(self));
	rb_ary_push(result,_get_d_y(self));
	rb_ary_push(result,_get_d_z(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 *
 * loads a string into an Quaternion.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	_set_d_z(self,rb_ary_pop(result));
	_set_d_y(self,rb_ary_pop(result));
	_set_d_x(self,rb_ary_pop(result));
	_set_d_w(self,rb_ary_pop(result));
	return self;
}


/*
 * call-seq:
 *   ==(quaternion) -> Boolean
 *
 * compare with Quaternion.
*/
VALUE _equal(VALUE self,VALUE other)
{
	return wrap(*_self == wrap<CEGUI::Quaternion>(other));
}


}
/*
 * Document-class: CEGUI::Quaternion
 *
 * This class represents an 3dimensional Vector.
*/
/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
/* Document-attr: z
 * the z Cordinate */
void Init_CeguiQuaternion(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiQuaternion,"x",1,1);
	rb_define_attr(rb_cCeguiQuaternion,"y",1,1);
	rb_define_attr(rb_cCeguiQuaternion,"z",1,1);
#endif
	using namespace CeguiQuaternion;
	rb_cCeguiQuaternion = rb_define_class_under(rb_mCegui,"Quaternion",rb_cObject);
	rb_define_alloc_func(rb_cCeguiQuaternion,_alloc);
	rb_define_method(rb_cCeguiQuaternion,"initialize",RUBY_METHOD_FUNC(_initialize),3);
	rb_define_private_method(rb_cCeguiQuaternion,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cCeguiQuaternion,"w",_get_d_w,_set_d_w);
	rb_define_attr_method(rb_cCeguiQuaternion,"x",_get_d_x,_set_d_x);
	rb_define_attr_method(rb_cCeguiQuaternion,"y",_get_d_y,_set_d_y);
	rb_define_attr_method(rb_cCeguiQuaternion,"z",_get_d_z,_set_d_z);

	rb_define_method(rb_cCeguiQuaternion,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiQuaternion,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiQuaternion,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiQuaternion,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cCeguiQuaternion,"==",RUBY_METHOD_FUNC(_equal),1);

	rb_define_method(rb_cCeguiQuaternion,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiQuaternion,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiQuaternion,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiQuaternion,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}
