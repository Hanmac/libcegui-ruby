#include "ceguiuvector2.hpp"
#include "ceguiurect.hpp"
#define _self wrap<CEGUI::URect*>(self)
VALUE rb_cCeguiURect;

VALUE CeguiURect_alloc(VALUE self)
{
	return wrap(new CEGUI::URect);
}
macro_attr_prop(URect,d_min,CEGUI::UVector2)
macro_attr_prop(URect,d_max,CEGUI::UVector2)

macro_attr(URect,Position,CEGUI::UVector2)
macro_attr(URect,Size,CEGUI::USize)
macro_attr(URect,Width,CEGUI::UDim)
macro_attr(URect,Height,CEGUI::UDim)
/*

VALUE CeguiURect_initialize(VALUE self,VALUE top,VALUE left,VALUE bottom,VALUE right)
{
	CeguiURect_set_d_top(self,top);
	CeguiURect_set_d_left(self,left);
	CeguiURect_set_d_bottom(self,bottom);
	CeguiURect_set_d_right(self,right);
	return self;
}
VALUE CeguiURect_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiURect_set_d_top(self,CeguiURect_get_d_top(other));
	CeguiURect_set_d_left(self,CeguiURect_get_d_left(other));
	CeguiURect_set_d_bottom(self,CeguiURect_get_d_bottom(other));
	CeguiURect_set_d_right(self,CeguiURect_get_d_right(other));
	return result;
}
//*/

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiURect_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(CeguiURect_get_d_min(self),rb_intern("inpect"),0);
	array[3]=rb_funcall(CeguiURect_get_d_max(self),rb_intern("inpect"),0);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE CeguiURect_swap(VALUE self,VALUE other)
{
	CEGUI::URect* cother = wrap<CEGUI::URect*>(other);
	std::swap(_self->d_min,cother->d_min);
	std::swap(_self->d_max,cother->d_max);
	return self;
}
/*
*/
VALUE CeguiURect_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::URect>(other));
}
/*
*/
VALUE CeguiURect_mal(VALUE self,VALUE other)
{
	return wrap(*_self * wrap<CEGUI::UDim>(other));
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined udim values.
 * ===Return value
 * Integer
*/
VALUE CeguiURect_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiURect_get_d_min(self));
	rb_ary_push(result,CeguiURect_get_d_max(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a URect into an string.
*/
VALUE CeguiURect_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->d_min.d_x.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_min.d_x.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_min.d_y.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_min.d_y.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_max.d_x.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_max.d_x.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_max.d_y.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_max.d_y.d_offset));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddddddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an URect.
*/
VALUE CeguiURect_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddddddd"));
	_self->d_max.d_y.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_max.d_y.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_max.d_x.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_max.d_x.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_min.d_y.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_min.d_y.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_min.d_x.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_min.d_x.d_scale=NUM2DBL(rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::URect
 * 
 * 
*/ 
/* Document-attr: min
 * the min Cordinate */
/* Document-attr: max
 * the max Cordinate */
void Init_CeguiURect(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiURect,"min",1,1);
	rb_define_attr(rb_cCeguiURect,"max",1,1);
	rb_define_attr(rb_cCeguiURect,"position",1,1);
	rb_define_attr(rb_cCeguiURect,"size",1,1);
	rb_define_attr(rb_cCeguiURect,"width",1,1);
	rb_define_attr(rb_cCeguiURect,"height",1,1);
#endif
	rb_cCeguiURect = rb_define_class_under(rb_mCegui,"UDim",rb_cObject);
	rb_define_alloc_func(rb_cCeguiURect,CeguiURect_alloc);
//	rb_define_method(rb_cCeguiURect,"initialize",RUBY_METHOD_FUNC(CeguiURect_initialize),2);
//	rb_define_private_method(rb_cCeguiURect,"initialize_copy",RUBY_METHOD_FUNC(CeguiURect_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiURect,"min",CeguiURect_get_d_min,CeguiURect_set_d_min);
	rb_define_attr_method(rb_cCeguiURect,"max",CeguiURect_get_d_max,CeguiURect_set_d_max);
	
	rb_define_attr_method(rb_cCeguiURect,"position",CeguiURect_getPosition,CeguiURect_setPosition);
	rb_define_attr_method(rb_cCeguiURect,"size",CeguiURect_getSize,CeguiURect_setSize);
	rb_define_attr_method(rb_cCeguiURect,"width",CeguiURect_getWidth,CeguiURect_setWidth);
	rb_define_attr_method(rb_cCeguiURect,"height",CeguiURect_getHeight,CeguiURect_setHeight);
	
	rb_define_method(rb_cCeguiURect,"inspect",RUBY_METHOD_FUNC(CeguiURect_inspect),0);

	rb_define_method(rb_cCeguiURect,"+",RUBY_METHOD_FUNC(CeguiURect_plus),1);
	rb_define_method(rb_cCeguiURect,"*",RUBY_METHOD_FUNC(CeguiURect_mal),1);

	rb_define_method(rb_cCeguiURect,"hash",RUBY_METHOD_FUNC(CeguiURect_hash),0);

	rb_define_method(rb_cCeguiURect,"swap",RUBY_METHOD_FUNC(CeguiURect_swap),1);

	rb_define_method(rb_cCeguiURect,"marshal_dump",RUBY_METHOD_FUNC(CeguiURect_marshal_dump),0);
	rb_define_method(rb_cCeguiURect,"marshal_load",RUBY_METHOD_FUNC(CeguiURect_marshal_load),1);

}
