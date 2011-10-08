#include "ceguivector3.hpp"
#define _self wrap<CEGUI::Vector3f*>(self)
VALUE rb_cCeguiVector3;

VALUE CeguiVector3_alloc(VALUE self)
{
	return wrap(new CEGUI::Vector3f);
}
macro_attr_prop(Vector3,d_x,float)
macro_attr_prop(Vector3,d_y,float)
macro_attr_prop(Vector3,d_z,float)
/*
*/
VALUE CeguiVector3_initialize(VALUE self,VALUE x,VALUE y,VALUE z)
{
	CeguiVector3_set_d_x(self,x);
	CeguiVector3_set_d_y(self,y);
	CeguiVector3_set_d_z(self,z);
	return self;
}
/*
*/
VALUE CeguiVector3_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiVector3_set_d_x(self,CeguiVector3_get_d_x(other));
	CeguiVector3_set_d_y(self,CeguiVector3_get_d_y(other));
	CeguiVector3_set_d_z(self,CeguiVector3_get_d_z(other));
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
VALUE CeguiVector3_inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiVector3_get_d_x(self);
	array[3]=CeguiVector3_get_d_y(self);
	array[4]=CeguiVector3_get_d_z(self);
	return rb_f_sprintf(5,array);
}
/*
*/
VALUE CeguiVector3_minusself(VALUE self)
{
	return wrap(CEGUI::Vector3f(- _self->d_x,- _self->d_y,- _self->d_z));
}
/*
*/
VALUE CeguiVector3_swap(VALUE self,VALUE other)
{
	CEGUI::Vector3f* cother = wrap<CEGUI::Vector3f*>(other);
	std::swap(_self->d_x,cother->d_x);
	std::swap(_self->d_y,cother->d_y);
	std::swap(_self->d_z,cother->d_z);
	return self;
}
/*
*/
VALUE CeguiVector3_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Vector3f>(other));
}
/*
*/
VALUE CeguiVector3_minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::Vector3f>(other));
}


/*
*/
VALUE CeguiVector3_mal(VALUE self,VALUE other)
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
VALUE CeguiVector3_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiVector3_get_d_x(self));
	rb_ary_push(result,CeguiVector3_get_d_y(self));
	rb_ary_push(result,CeguiVector3_get_d_z(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector3 into an string.
*/
VALUE CeguiVector3_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiVector3_get_d_x(self));
	rb_ary_push(result,CeguiVector3_get_d_y(self));
	rb_ary_push(result,CeguiVector3_get_d_z(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector3.
*/
VALUE CeguiVector3_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ddd"));
	CeguiVector3_set_d_z(self,rb_ary_pop(result));
	CeguiVector3_set_d_y(self,rb_ary_pop(result));
	CeguiVector3_set_d_x(self,rb_ary_pop(result));
	return self;
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
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiVector3,"x",1,1);
	rb_define_attr(rb_cCeguiVector3,"y",1,1);
	rb_define_attr(rb_cCeguiVector3,"z",1,1);
#endif
	rb_cCeguiVector3 = rb_define_class_under(rb_mCegui,"Vector3",rb_cObject);
	rb_define_alloc_func(rb_cCeguiVector3,CeguiVector3_alloc);
	rb_define_method(rb_cCeguiVector3,"initialize",RUBY_METHOD_FUNC(CeguiVector3_initialize),3);
	rb_define_private_method(rb_cCeguiVector3,"initialize_copy",RUBY_METHOD_FUNC(CeguiVector3_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiVector3,"x",CeguiVector3_get_d_x,CeguiVector3_set_d_x);
	rb_define_attr_method(rb_cCeguiVector3,"y",CeguiVector3_get_d_y,CeguiVector3_set_d_y);
	rb_define_attr_method(rb_cCeguiVector3,"z",CeguiVector3_get_d_z,CeguiVector3_set_d_z);

	rb_define_method(rb_cCeguiVector3,"inspect",RUBY_METHOD_FUNC(CeguiVector3_inspect),0);

	rb_define_method(rb_cCeguiVector3,"+",RUBY_METHOD_FUNC(CeguiVector3_plus),1);
	rb_define_method(rb_cCeguiVector3,"-",RUBY_METHOD_FUNC(CeguiVector3_minus),1);
	rb_define_method(rb_cCeguiVector3,"*",RUBY_METHOD_FUNC(CeguiVector3_mal),1);

	rb_define_method(rb_cCeguiVector3,"hash",RUBY_METHOD_FUNC(CeguiVector3_hash),0);

	rb_define_method(rb_cCeguiVector3,"swap",RUBY_METHOD_FUNC(CeguiVector3_swap),1);

	rb_define_method(rb_cCeguiVector3,"marshal_dump",RUBY_METHOD_FUNC(CeguiVector3_marshal_dump),0);
	rb_define_method(rb_cCeguiVector3,"marshal_load",RUBY_METHOD_FUNC(CeguiVector3_marshal_load),1);

}
