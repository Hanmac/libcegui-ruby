#include "ceguisize.hpp"
#define _self wrap<CEGUI::Sizef*>(self)
VALUE rb_cCeguiSize;

macro_attr_prop(Size,d_width,float)
macro_attr_prop(Size,d_height,float)


VALUE CeguiSize_alloc(VALUE self)
{
	return wrap(new CEGUI::Sizef);
}
/*
*/
VALUE CeguiSize_initialize(VALUE self,VALUE x,VALUE y)
{
	CeguiSize_set_d_width(self,x);
	CeguiSize_set_d_height(self,y);
	return self;
}
/*
*/
VALUE CeguiSize_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiSize_set_d_width(self,CeguiSize_get_d_width(other));
	CeguiSize_set_d_height(self,CeguiSize_get_d_height(other));
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
VALUE CeguiSize_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiSize_get_d_width(self);
	array[3]=CeguiSize_get_d_height(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE CeguiSize_minusself(VALUE self)
{
	return wrap(CEGUI::Sizef(- _self->d_width,- _self->d_height));
}
/*
*/
VALUE CeguiSize_swap(VALUE self,VALUE other)
{
	CEGUI::Sizef* cother = wrap<CEGUI::Sizef*>(other);
	std::swap(_self->d_width,cother->d_width);
	std::swap(_self->d_height,cother->d_height);
	return self;
}
/*
*/
VALUE CeguiSize_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Sizef>(other));
}
/*
*/
VALUE CeguiSize_minus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Sizef>(CeguiSize_minusself(other)));
}
/*
*/
VALUE CeguiSize_mal(VALUE self,VALUE other)
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
VALUE CeguiSize_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiSize_get_d_width(self));
	rb_ary_push(result,CeguiSize_get_d_height(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Size into an string.
*/
VALUE CeguiSize_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiSize_get_d_width(self));
	rb_ary_push(result,CeguiSize_get_d_height(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Size.
*/
VALUE CeguiSize_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	CeguiSize_set_d_height(self,rb_ary_pop(result));
	CeguiSize_set_d_width(self,rb_ary_pop(result));
	return self;
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
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiSize,"width",1,1);
	rb_define_attr(rb_cCeguiSize,"height",1,1);
#endif
	rb_cCeguiSize = rb_define_class_under(rb_mCegui,"Size",rb_cObject);
	rb_define_alloc_func(rb_cCeguiSize,CeguiSize_alloc);
	rb_define_method(rb_cCeguiSize,"initialize",RUBY_METHOD_FUNC(CeguiSize_initialize),2);
	rb_define_private_method(rb_cCeguiSize,"initialize_copy",RUBY_METHOD_FUNC(CeguiSize_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiSize,"width",CeguiSize_get_d_width,CeguiSize_set_d_width);
	rb_define_attr_method(rb_cCeguiSize,"height",CeguiSize_get_d_height,CeguiSize_set_d_height);

	rb_define_method(rb_cCeguiSize,"inspect",RUBY_METHOD_FUNC(CeguiSize_inspect),0);
	rb_define_method(rb_cCeguiSize,"-@",RUBY_METHOD_FUNC(CeguiSize_minusself),0);

	rb_define_method(rb_cCeguiSize,"+",RUBY_METHOD_FUNC(CeguiSize_plus),1);
	rb_define_method(rb_cCeguiSize,"-",RUBY_METHOD_FUNC(CeguiSize_minus),1);
	rb_define_method(rb_cCeguiSize,"*",RUBY_METHOD_FUNC(CeguiSize_mal),1);

	rb_define_method(rb_cCeguiSize,"hash",RUBY_METHOD_FUNC(CeguiSize_hash),0);

	rb_define_method(rb_cCeguiSize,"swap",RUBY_METHOD_FUNC(CeguiSize_swap),1);

	rb_define_method(rb_cCeguiSize,"marshal_dump",RUBY_METHOD_FUNC(CeguiSize_marshal_dump),0);
	rb_define_method(rb_cCeguiSize,"marshal_load",RUBY_METHOD_FUNC(CeguiSize_marshal_load),1);

}
