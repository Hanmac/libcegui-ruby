#include "ceguivector3.hpp"
#define _self wrap<CEGUI::Vector3f*>(self)
VALUE rb_cCeguiVector3;

namespace CeguiVector3 {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::Vector3f);
}
macro_attr_prop(d_x,float)
macro_attr_prop(d_y,float)
macro_attr_prop(d_z,float)
/*
*/
VALUE _initialize(VALUE self,VALUE x,VALUE y,VALUE z)
{
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
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_d_x(self);
	array[3]=_get_d_y(self);
	array[4]=_get_d_z(self);
	return rb_f_sprintf(5,array);
}
/*
*/
VALUE _minusself(VALUE self)
{
	return wrap(CEGUI::Vector3f(- _self->d_x,- _self->d_y,- _self->d_z));
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::Vector3f* cother = wrap<CEGUI::Vector3f*>(other);
	std::swap(_self->d_x,cother->d_x);
	std::swap(_self->d_y,cother->d_y);
	std::swap(_self->d_z,cother->d_z);
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Vector3f>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::Vector3f>(other));
}


/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * NUM2DBL(other));
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vector2 values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_x(self));
	rb_ary_push(result,_get_d_y(self));
	rb_ary_push(result,_get_d_z(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector3 into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_x(self));
	rb_ary_push(result,_get_d_y(self));
	rb_ary_push(result,_get_d_z(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector3.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	_set_d_z(self,rb_ary_pop(result));
	_set_d_y(self,rb_ary_pop(result));
	_set_d_x(self,rb_ary_pop(result));
	return self;
}

/*
 * call-seq:
 *   ==(vector3) -> Boolean
 *
 * compare with Vector3.
*/
VALUE _equal(VALUE self,VALUE other)
{
	return wrap(*_self == wrap<CEGUI::Vector3f>(other));
}



}
/*
 * Document-class: CEGUI::Vector3
 * 
 * This class represents an 3dimensional Vector.
*/ 
/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
/* Document-attr: z
 * the z Cordinate */
void Init_CeguiVector3(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiVector3,"x",1,1);
	rb_define_attr(rb_cCeguiVector3,"y",1,1);
	rb_define_attr(rb_cCeguiVector3,"z",1,1);
#endif
	using namespace CeguiVector3;
	rb_cCeguiVector3 = rb_define_class_under(rb_mCegui,"Vector3",rb_cObject);
	rb_define_alloc_func(rb_cCeguiVector3,_alloc);
	rb_define_method(rb_cCeguiVector3,"initialize",RUBY_METHOD_FUNC(_initialize),3);
	rb_define_private_method(rb_cCeguiVector3,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiVector3,"x",_get_d_x,_set_d_x);
	rb_define_attr_method(rb_cCeguiVector3,"y",_get_d_y,_set_d_y);
	rb_define_attr_method(rb_cCeguiVector3,"z",_get_d_z,_set_d_z);

	rb_define_method(rb_cCeguiVector3,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiVector3,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiVector3,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiVector3,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cCeguiVector3,"==",RUBY_METHOD_FUNC(_equal),1);


	rb_define_method(rb_cCeguiVector3,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiVector3,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiVector3,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiVector3,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}
