#include "ceguiuvector2.hpp"
#include "ceguiurect.hpp"
#define _self wrap<CEGUI::URect*>(self)
VALUE rb_cCeguiURect;

namespace CeguiURect
{
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::URect);
}
macro_attr_prop(d_min,CEGUI::UVector2)
macro_attr_prop(d_max,CEGUI::UVector2)

macro_attr(Position,CEGUI::UVector2)
macro_attr(Size,CEGUI::USize)
macro_attr(Width,CEGUI::UDim)
macro_attr(Height,CEGUI::UDim)


VALUE _get_d_top(VALUE self)
{
	return wrap(_self->top());
}
VALUE _get_d_bottom(VALUE self)
{
	return wrap(_self->bottom());
}

VALUE _get_d_left(VALUE self)
{
	return wrap(_self->left());
}
VALUE _get_d_right(VALUE self)
{
	return wrap(_self->right());
}


VALUE _set_d_top(VALUE self,VALUE v)
{
	_self->top(wrap<CEGUI::UDim>(v));
	return v;
}
VALUE _set_d_bottom(VALUE self,VALUE v)
{
	_self->bottom(wrap<CEGUI::UDim>(v));
	return v;
}

VALUE _set_d_left(VALUE self,VALUE v)
{
	_self->left(wrap<CEGUI::UDim>(v));
	return v;
}
VALUE _set_d_right(VALUE self,VALUE v)
{
	_self->right(wrap<CEGUI::UDim>(v));
	return v;
}

/*

VALUE _initialize(VALUE self,VALUE top,VALUE left,VALUE bottom,VALUE right)
{
	_set_d_top(self,top);
	_set_d_left(self,left);
	_set_d_bottom(self,bottom);
	_set_d_right(self,right);
	return self;
}
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_d_top(self,_get_d_top(other));
	_set_d_left(self,_get_d_left(other));
	_set_d_bottom(self,_get_d_bottom(other));
	_set_d_right(self,_get_d_right(other));
	return result;
}
//*/

/*
 *
 */
VALUE _to_s(VALUE self)
{
	return wrap(CEGUI::PropertyHelper<CEGUI::URect>::toString(*_self));
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
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::URect* cother = wrap<CEGUI::URect*>(other);
	std::swap(_self->d_min,cother->d_min);
	std::swap(_self->d_max,cother->d_max);
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::URect>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	if (rb_obj_is_kind_of(other, rb_cNumeric))
		return wrap(*_self * NUM2DBL(other));
	else
		return wrap(*_self * wrap<CEGUI::UDim>(other));
}


/*
 * call-seq:
 *   ==(URect) -> Boolean
 *
 * compare with URect.
*/
VALUE _equal(VALUE self,VALUE other)
{
	if(self == other)
		return Qtrue;
	if(!is_wrapable<CEGUI::URect>(other))
		return Qfalse;
	return wrap(*_self == wrap<CEGUI::URect>(other));
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
	rb_ary_push(result,_get_d_min(self));
	rb_ary_push(result,_get_d_max(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a URect into an string.
*/
VALUE _marshal_dump(VALUE self)
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

	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an URect.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));

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
/* Document-attr: top
 * the top Cordinate */
/* Document-attr: left
 * the left Cordinate */
/* Document-attr: bottom
 * the bottom Cordinate */
/* Document-attr: right
 * the right Cordinate */
void Init_CeguiURect(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiURect,"top",1,1);
	rb_define_attr(rb_cCeguiURect,"left",1,1);
	rb_define_attr(rb_cCeguiURect,"bottom",1,1);
	rb_define_attr(rb_cCeguiURect,"right",1,1);

	rb_define_attr(rb_cCeguiURect,"min",1,1);
	rb_define_attr(rb_cCeguiURect,"max",1,1);
	
	rb_define_attr(rb_cCeguiURect,"position",1,1);
	rb_define_attr(rb_cCeguiURect,"height",1,1);
	rb_define_attr(rb_cCeguiURect,"width",1,1);
	rb_define_attr(rb_cCeguiURect,"size",1,1);
#endif
	using namespace CeguiURect;

	rb_cCeguiURect = rb_define_class_under(rb_mCegui,"URect",rb_cObject);
	rb_define_alloc_func(rb_cCeguiURect,_alloc);
//	rb_define_method(rb_cCeguiURect,"initialize",RUBY_METHOD_FUNC(_initialize),2);
//	rb_define_private_method(rb_cCeguiURect,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiURect,"min",_get_d_min,_set_d_min);
	rb_define_attr_method(rb_cCeguiURect,"max",_get_d_max,_set_d_max);
	
	rb_define_attr_method(rb_cCeguiURect,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cCeguiURect,"size",_getSize,_setSize);
	rb_define_attr_method(rb_cCeguiURect,"width",_getWidth,_setWidth);
	rb_define_attr_method(rb_cCeguiURect,"height",_getHeight,_setHeight);
	
	
	rb_define_attr_method(rb_cCeguiURect,"top",_get_d_top,_set_d_top);
	rb_define_attr_method(rb_cCeguiURect,"bottom",_get_d_bottom,_set_d_bottom);
	rb_define_attr_method(rb_cCeguiURect,"left",_get_d_left,_set_d_left);
	rb_define_attr_method(rb_cCeguiURect,"right",_get_d_left,_set_d_right);

	
	rb_define_method(rb_cCeguiURect,"to_s",RUBY_METHOD_FUNC(_to_s),0);
	rb_define_method(rb_cCeguiURect,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiURect,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiURect,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cCeguiURect,"==",RUBY_METHOD_FUNC(_equal),1);

	rb_define_method(rb_cCeguiURect,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiURect,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiURect,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiURect,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

}
