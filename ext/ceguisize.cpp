#include "ceguisize.hpp"
#define _self wrap<CEGUI::Sizef*>(self)
VALUE rb_cCeguiSize;

namespace CeguiSize {

macro_attr_prop(d_width,float)
macro_attr_prop(d_height,float)


VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::Sizef);
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
VALUE _minusself(VALUE self)
{
	return wrap(CEGUI::Sizef(- _self->d_width,- _self->d_height));
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::Sizef* cother = wrap<CEGUI::Sizef*>(other);
	std::swap(_self->d_width,cother->d_width);
	std::swap(_self->d_height,cother->d_height);
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Sizef>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Sizef>(_minusself(other)));
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
 * Document-class: CEGUI::Sizef
 * 
 * This class represents an Size
*/ 
/* Document-attr: width
 * the width size */
/* Document-attr: height
 * the height size */
void Init_CeguiSize(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiSize,"width",1,1);
	rb_define_attr(rb_cCeguiSize,"height",1,1);
#endif
	using namespace CeguiSize;

	rb_cCeguiSize = rb_define_class_under(rb_mCegui,"Size",rb_cObject);
	rb_define_alloc_func(rb_cCeguiSize,_alloc);
	rb_define_method(rb_cCeguiSize,"initialize",RUBY_METHOD_FUNC(_initialize),2);
	rb_define_private_method(rb_cCeguiSize,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiSize,"width",_get_d_width,_set_d_width);
	rb_define_attr_method(rb_cCeguiSize,"height",_get_d_height,_set_d_height);

	rb_define_method(rb_cCeguiSize,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cCeguiSize,"-@",RUBY_METHOD_FUNC(_minusself),0);

	rb_define_method(rb_cCeguiSize,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiSize,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiSize,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cCeguiSize,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiSize,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiSize,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiSize,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}
