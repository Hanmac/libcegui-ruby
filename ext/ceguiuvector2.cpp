#include "ceguiuvector2.hpp"
#define _self wrap<CEGUI::UVector2*>(self)
VALUE rb_cCeguiUVector2;

namespace CeguiUVector2 {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::UVector2);
}
macro_attr_prop(d_x,CEGUI::UDim)
macro_attr_prop(d_y,CEGUI::UDim)
/*
*/
VALUE _initialize(VALUE self,VALUE x,VALUE y)
{
	_set_d_x(self,x);
	_set_d_y(self,y);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_d_x(self,_get_d_x(other));
	_set_d_y(self,_get_d_y(other));
	return result;
}
/*
 *
 */
VALUE _to_s(VALUE self)
{
	return wrap(CEGUI::PropertyHelper<CEGUI::UVector2>::toString(*_self));
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
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=self;
	return rb_f_sprintf(3,array);
}
/*
*/
VALUE _minusself(VALUE self)
{
	return wrap(CEGUI::UVector2(CEGUI::UDim(- _self->d_x.d_scale,- _self->d_x.d_offset),CEGUI::UDim(- _self->d_y.d_scale,- _self->d_y.d_offset)));
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::UVector2* cother = wrap<CEGUI::UVector2*>(other);
	std::swap(_self->d_x,cother->d_x);
	std::swap(_self->d_y,cother->d_y);
	return self;
}

/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::UVector2>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::UVector2>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cCeguiUDim))
		return wrap(*_self * wrap<CEGUI::UDim>(other));
	else
		return wrap(*_self * wrap<CEGUI::UVector2>(other));
}
/*
*/
VALUE _durch(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cCeguiUDim))
		return wrap(*_self / wrap<CEGUI::UDim>(other));
	else
		return wrap(*_self / wrap<CEGUI::UVector2>(other));
}

/*
 * call-seq:
 *   ==(uvector2) -> Boolean
 *
 * compare with UVector2.
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(self == other)
		return Qtrue;
	if(!is_wrapable<CEGUI::UVector2>(other))
		return Qfalse;
	return wrap(*_self == wrap<CEGUI::UVector2>(other));
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
	rb_ary_push(result,_get_d_x(self));
	rb_ary_push(result,_get_d_y(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a UVector2 into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->d_x.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_x.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_y.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_y.d_offset));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an UVector2.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	_self->d_y.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_y.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_x.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_x.d_scale=NUM2DBL(rb_ary_pop(result));
	return self;
}

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
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiUVector2,"x",1,1);
	rb_define_attr(rb_cCeguiUVector2,"y",1,1);
#endif
	using namespace CeguiUVector2;
	rb_cCeguiUVector2 = rb_define_class_under(rb_mCegui,"UVector2",rb_cObject);
	rb_define_alloc_func(rb_cCeguiUVector2,_alloc);
	rb_define_method(rb_cCeguiUVector2,"initialize",RUBY_METHOD_FUNC(_initialize),2);
	rb_define_private_method(rb_cCeguiUVector2,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiUVector2,"x",_get_d_x,_set_d_x);
	rb_define_attr_method(rb_cCeguiUVector2,"y",_get_d_y,_set_d_y);

	rb_define_method(rb_cCeguiUVector2,"to_s",RUBY_METHOD_FUNC(_to_s),0);

	rb_define_method(rb_cCeguiUVector2,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiUVector2,"-@",RUBY_METHOD_FUNC(_minusself),0);

	rb_define_method(rb_cCeguiUVector2,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiUVector2,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiUVector2,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cCeguiUVector2,"/",RUBY_METHOD_FUNC(_durch),1);

	rb_define_method(rb_cCeguiUVector2,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiUVector2,"==",RUBY_METHOD_FUNC(_equal),1);

	rb_define_method(rb_cCeguiUVector2,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiUVector2,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiUVector2,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}
