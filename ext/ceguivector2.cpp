#include "ceguivector2.hpp"
#define _self wrap<CEGUI::Vector2f*>(self)
VALUE rb_cCeguiVector2;

VALUE CeguiVector2_alloc(VALUE self)
{
	return wrap(new CEGUI::Vector2f);
}
macro_attr_prop(Vector2,d_x,float)
macro_attr_prop(Vector2,d_y,float)
/*
*/
VALUE CeguiVector2_initialize(VALUE self,VALUE x,VALUE y)
{
	CeguiVector2_set_d_x(self,x);
	CeguiVector2_set_d_y(self,y);
	return self;
}
/*
*/
VALUE CeguiVector2_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiVector2_set_d_x(self,CeguiVector2_get_d_x(other));
	CeguiVector2_set_d_y(self,CeguiVector2_get_d_y(other));
	return result;
}
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiVector2_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiVector2_get_d_x(self);
	array[3]=CeguiVector2_get_d_y(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE CeguiVector2_minusself(VALUE self)
{
	return wrap(CEGUI::Vector2f(- _self->d_x,- _self->d_y));
}
/*
*/
VALUE CeguiVector2_swap(VALUE self,VALUE other)
{
	CEGUI::Vector2f* cother = wrap<CEGUI::Vector2f*>(other);
	std::swap(_self->d_x,cother->d_x);
	std::swap(_self->d_y,cother->d_y);
	return self;
}
/*
*/
VALUE CeguiVector2_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Vector2f>(other));
}
/*
*/
VALUE CeguiVector2_minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::Vector2f>(other));
}
/*
*/
VALUE CeguiVector2_mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cNumeric))
		return wrap(*_self * NUM2DBL(other));
	else
		return wrap(*_self * wrap<CEGUI::Vector2f>(other));
}
/*
*/
VALUE CeguiVector2_durch(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cNumeric))
		return wrap(*_self / NUM2DBL(other));
	else
		return wrap(*_self / wrap<CEGUI::Vector2f>(other));
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vector2 values.
 * ===Return value
 * Integer
*/
VALUE CeguiVector2_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiVector2_get_d_x(self));
	rb_ary_push(result,CeguiVector2_get_d_y(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vector2 into an string.
*/
VALUE CeguiVector2_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiVector2_get_d_x(self));
	rb_ary_push(result,CeguiVector2_get_d_y(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector2.
*/
VALUE CeguiVector2_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	CeguiVector2_set_d_y(self,rb_ary_pop(result));
	CeguiVector2_set_d_x(self,rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::Vector2
 * 
 * This class represents an 2dimensional Vector.
*/ 
/* Document-attr: x
 * the x Cordinate */
/* Document-attr: y
 * the y Cordinate */
void Init_CeguiVector2(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiVector2,"x",1,1);
	rb_define_attr(rb_cCeguiVector2,"y",1,1);
#endif
	rb_cCeguiVector2 = rb_define_class_under(rb_mCegui,"Vector2",rb_cObject);
	rb_define_alloc_func(rb_cCeguiVector2,CeguiVector2_alloc);
	rb_define_method(rb_cCeguiVector2,"initialize",RUBY_METHOD_FUNC(CeguiVector2_initialize),2);
	rb_define_private_method(rb_cCeguiVector2,"initialize_copy",RUBY_METHOD_FUNC(CeguiVector2_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiVector2,"x",CeguiVector2_get_d_x,CeguiVector2_set_d_x);
	rb_define_attr_method(rb_cCeguiVector2,"y",CeguiVector2_get_d_y,CeguiVector2_set_d_y);

	rb_define_method(rb_cCeguiVector2,"inspect",RUBY_METHOD_FUNC(CeguiVector2_inspect),0);
	rb_define_method(rb_cCeguiVector2,"-@",RUBY_METHOD_FUNC(CeguiVector2_minusself),0);

	rb_define_method(rb_cCeguiVector2,"+",RUBY_METHOD_FUNC(CeguiVector2_plus),1);
	rb_define_method(rb_cCeguiVector2,"-",RUBY_METHOD_FUNC(CeguiVector2_minus),1);
	rb_define_method(rb_cCeguiVector2,"*",RUBY_METHOD_FUNC(CeguiVector2_mal),1);
	rb_define_method(rb_cCeguiVector2,"/",RUBY_METHOD_FUNC(CeguiVector2_durch),1);
	
	rb_define_method(rb_cCeguiVector2,"hash",RUBY_METHOD_FUNC(CeguiVector2_hash),0);

	rb_define_method(rb_cCeguiVector2,"swap",RUBY_METHOD_FUNC(CeguiVector2_swap),1);

	rb_define_method(rb_cCeguiVector2,"marshal_dump",RUBY_METHOD_FUNC(CeguiVector2_marshal_dump),0);
	rb_define_method(rb_cCeguiVector2,"marshal_load",RUBY_METHOD_FUNC(CeguiVector2_marshal_load),1);

}
