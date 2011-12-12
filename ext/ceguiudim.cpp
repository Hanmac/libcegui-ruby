#include "ceguiudim.hpp"
#define _self wrap<CEGUI::UDim*>(self)
VALUE rb_cCeguiUDim;

namespace CeguiUDim {
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::UDim(0,0));
}
macro_attr_prop(d_scale,float)
macro_attr_prop(d_offset,float)
/*
*/
VALUE _initialize(VALUE self,VALUE scale,VALUE offset)
{
	_set_d_scale(self,scale);
	_set_d_offset(self,offset);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_d_scale(self,_get_d_scale(other));
	_set_d_offset(self,_get_d_offset(other));
	return result;
}
/*
 * call-seq:
 *   udim.inspect -> String
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
	array[2]=_get_d_scale(self);
	array[3]=_get_d_offset(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE _minusself(VALUE self)
{
	return wrap(CEGUI::UDim(- _self->d_scale,- _self->d_offset));
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::UDim* cother = wrap<CEGUI::UDim*>(other);
	std::swap(_self->d_scale,cother->d_scale);
	std::swap(_self->d_offset,cother->d_offset);
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::UDim>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::UDim>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * wrap<CEGUI::UDim>(other));
}
/*
*/
VALUE _durch(VALUE self,VALUE other)
{
	return wrap(*_self / wrap<CEGUI::UDim>(other));
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined udim values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_scale(self));
	rb_ary_push(result,_get_d_offset(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a UDim into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_scale(self));
	rb_ary_push(result,_get_d_offset(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an UDim.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	_set_d_offset(self,rb_ary_pop(result));
	_set_d_scale(self,rb_ary_pop(result));
	return self;
}
}
/*
 * Document-class: CEGUI::UDim
 * 
 * 
*/ 
/* Document-attr: scale
 * the scale Cordinate */
/* Document-attr: offset
 * the offset Cordinate */
void Init_CeguiUDim(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiUDim,"scale",1,1);
	rb_define_attr(rb_cCeguiUDim,"offset",1,1);
#endif
	using namespace CeguiUDim;
	
	rb_cCeguiUDim = rb_define_class_under(rb_mCegui,"UDim",rb_cObject);
	rb_define_alloc_func(rb_cCeguiUDim,_alloc);
	rb_define_method(rb_cCeguiUDim,"initialize",RUBY_METHOD_FUNC(_initialize),2);
	rb_define_private_method(rb_cCeguiUDim,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiUDim,"scale",_get_d_scale,_set_d_scale);
	rb_define_attr_method(rb_cCeguiUDim,"offset",_get_d_offset,_set_d_offset);

	rb_define_method(rb_cCeguiUDim,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiUDim,"-@",RUBY_METHOD_FUNC(_minusself),0);

	rb_define_method(rb_cCeguiUDim,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiUDim,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiUDim,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cCeguiUDim,"/",RUBY_METHOD_FUNC(_durch),1);

	rb_define_method(rb_cCeguiUDim,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiUDim,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiUDim,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiUDim,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}
