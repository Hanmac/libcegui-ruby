#include "ceguivector2.hpp"
#define _self wrap<CEGUI::Vector2f*>(self)
VALUE rb_cCeguiVector2;

namespace CeguiVector2 {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::Vector2f);
}
macro_attr_prop(d_x,float)
macro_attr_prop(d_y,float)
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
	return wrap(CEGUI::PropertyHelper<CEGUI::Vector2f>::toString(*_self));
}

/*
 * call-seq:
 *   inspect -> String
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
	return wrap(CEGUI::Vector2f(- _self->d_x,- _self->d_y));
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::Vector2f* cother = wrap<CEGUI::Vector2f*>(other);
	std::swap(_self->d_x,cother->d_x);
	std::swap(_self->d_y,cother->d_y);
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Vector2f>(other));
}
/*
*/
VALUE _minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::Vector2f>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cNumeric))
		return wrap(*_self * NUM2DBL(other));
	else
		return wrap(*_self * wrap<CEGUI::Vector2f>(other));
}
/*
*/
VALUE _durch(VALUE self,VALUE other)
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
 * packs a Vector2 into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_x(self));
	rb_ary_push(result,_get_d_y(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vector2.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	_set_d_y(self,rb_ary_pop(result));
	_set_d_x(self,rb_ary_pop(result));
	return self;
}
/*
 * call-seq:
 *   ==(vector2) -> Boolean
 *
 * compare with Vector2.
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(self == other)
		return Qtrue;
	if(!is_wrapable<CEGUI::Vector2f>(other))
		return Qfalse;
	return wrap(*_self == wrap<CEGUI::Vector2f>(other));
}


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
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiVector2,"x",1,1);
	rb_define_attr(rb_cCeguiVector2,"y",1,1);
#endif
	using namespace CeguiVector2;

	rb_cCeguiVector2 = rb_define_class_under(rb_mCegui,"Vector2",rb_cObject);
	rb_define_alloc_func(rb_cCeguiVector2,_alloc);
	rb_define_method(rb_cCeguiVector2,"initialize",RUBY_METHOD_FUNC(_initialize),2);
	rb_define_private_method(rb_cCeguiVector2,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiVector2,"x",_get_d_x,_set_d_x);
	rb_define_attr_method(rb_cCeguiVector2,"y",_get_d_y,_set_d_y);

	rb_define_method(rb_cCeguiVector2,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cCeguiVector2,"-@",RUBY_METHOD_FUNC(_minusself),0);

	rb_define_method(rb_cCeguiVector2,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiVector2,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiVector2,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cCeguiVector2,"/",RUBY_METHOD_FUNC(_durch),1);
	
	rb_define_method(rb_cCeguiVector2,"==",RUBY_METHOD_FUNC(_equal),1);

	rb_define_method(rb_cCeguiVector2,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiVector2,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiVector2,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiVector2,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}
