#include "ceguiuvector2.hpp"
#define _self wrap<CEGUI::UVector2*>(self)
VALUE rb_cCeguiUVector2;

VALUE CeguiUVector2_alloc(VALUE self)
{
	return wrap(new CEGUI::UVector2);
}
macro_attr_prop(UVector2,d_x,CEGUI::UDim)
macro_attr_prop(UVector2,d_y,CEGUI::UDim)
/*
*/
VALUE CeguiUVector2_initialize(VALUE self,VALUE x,VALUE y)
{
	CeguiUVector2_set_d_x(self,x);
	CeguiUVector2_set_d_y(self,y);
	return self;
}
/*
*/
VALUE CeguiUVector2_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiUVector2_set_d_x(self,CeguiUVector2_get_d_x(other));
	CeguiUVector2_set_d_y(self,CeguiUVector2_get_d_y(other));
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
VALUE CeguiUVector2_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(CeguiUVector2_get_d_x(self),rb_intern("inpect"),0);
	array[3]=rb_funcall(CeguiUVector2_get_d_y(self),rb_intern("inpect"),0);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE CeguiUVector2_minusself(VALUE self)
{
	return wrap(CEGUI::UVector2(CEGUI::UDim(- _self->d_x.d_scale,- _self->d_x.d_offset),CEGUI::UDim(- _self->d_y.d_scale,- _self->d_y.d_offset)));
}
/*
*/
VALUE CeguiUVector2_swap(VALUE self,VALUE other)
{
	CEGUI::UVector2* cother = wrap<CEGUI::UVector2*>(other);
	std::swap(_self->d_x,cother->d_x);
	std::swap(_self->d_y,cother->d_y);
	return self;
}

/*
*/
VALUE CeguiUVector2_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::UVector2>(other));
}
/*
*/
VALUE CeguiUVector2_minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::UVector2>(other));
}
/*
*/
VALUE CeguiUVector2_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cCeguiUDim))
		return wrap(*_self * wrap<CEGUI::UDim>(other));
	else
		return wrap(*_self * wrap<CEGUI::UVector2>(other));
}
/*
*/
VALUE CeguiUVector2_durch(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cCeguiUDim))
		return wrap(*_self / wrap<CEGUI::UDim>(other));
	else
		return wrap(*_self / wrap<CEGUI::UVector2>(other));
}

/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined udim values.
 * ===Return value
 * Integer
*/
VALUE CeguiUVector2_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiUVector2_get_d_x(self));
	rb_ary_push(result,CeguiUVector2_get_d_y(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a UVector2 into an string.
*/
VALUE CeguiUVector2_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->d_x.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_x.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_y.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_y.d_offset));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an UVector2.
*/
VALUE CeguiUVector2_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	_self->d_y.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_y.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_x.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_x.d_scale=NUM2DBL(rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::UVector2
 * 
 * 
*/ 
/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
void Init_CeguiUVector2(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiUVector2,"x",1,1);
	rb_define_attr(rb_cCeguiUVector2,"y",1,1);
#endif
	rb_cCeguiUVector2 = rb_define_class_under(rb_mCegui,"UDim",rb_cObject);
	rb_define_alloc_func(rb_cCeguiUVector2,CeguiUVector2_alloc);
	rb_define_method(rb_cCeguiUVector2,"initialize",RUBY_METHOD_FUNC(CeguiUVector2_initialize),2);
	rb_define_private_method(rb_cCeguiUVector2,"initialize_copy",RUBY_METHOD_FUNC(CeguiUVector2_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiUVector2,"x",CeguiUVector2_get_d_x,CeguiUVector2_set_d_x);
	rb_define_attr_method(rb_cCeguiUVector2,"y",CeguiUVector2_get_d_y,CeguiUVector2_set_d_y);

	rb_define_method(rb_cCeguiUVector2,"inspect",RUBY_METHOD_FUNC(CeguiUVector2_inspect),0);

	rb_define_method(rb_cCeguiUVector2,"-@",RUBY_METHOD_FUNC(CeguiUVector2_minusself),0);

	rb_define_method(rb_cCeguiUVector2,"+",RUBY_METHOD_FUNC(CeguiUVector2_plus),1);
	rb_define_method(rb_cCeguiUVector2,"-",RUBY_METHOD_FUNC(CeguiUVector2_minus),1);
	rb_define_method(rb_cCeguiUVector2,"*",RUBY_METHOD_FUNC(CeguiUVector2_mal),1);
	rb_define_method(rb_cCeguiUVector2,"/",RUBY_METHOD_FUNC(CeguiUVector2_durch),1);

	rb_define_method(rb_cCeguiUVector2,"hash",RUBY_METHOD_FUNC(CeguiUVector2_hash),0);

	rb_define_method(rb_cCeguiUVector2,"swap",RUBY_METHOD_FUNC(CeguiUVector2_swap),1);

	rb_define_method(rb_cCeguiUVector2,"marshal_dump",RUBY_METHOD_FUNC(CeguiUVector2_marshal_dump),0);
	rb_define_method(rb_cCeguiUVector2,"marshal_load",RUBY_METHOD_FUNC(CeguiUVector2_marshal_load),1);

}
