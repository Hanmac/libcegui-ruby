#include "ceguiexception.hpp"

#include "ceguisize.hpp"
#include "ceguivector2.hpp"

#include "ceguirect.hpp"

#define _self wrap<CEGUI::Rectf*>(self)
VALUE rb_cCeguiRect;

namespace CeguiRect {
macro_attr_prop(d_min,CEGUI::Vector2f)
macro_attr_prop(d_max,CEGUI::Vector2f)

macro_attr(Position,CEGUI::Vector2f)
macro_attr(Width,float)
macro_attr(Height,float)
macro_attr(Size,CEGUI::Sizef)

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::Rectf());
}

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
	_self->top(wrap<float>(v));
	return v;
}
VALUE _set_d_bottom(VALUE self,VALUE v)
{
	_self->bottom(wrap<float>(v));
	return v;
}

VALUE _set_d_left(VALUE self,VALUE v)
{
	_self->left(wrap<float>(v));
	return v;
}
VALUE _set_d_right(VALUE self,VALUE v)
{
	_self->right(wrap<float>(v));
	return v;
}


/*
*/
VALUE _initialize(VALUE self,VALUE min,VALUE max)
{
	_set_d_min(self,min);
	_set_d_max(self,max);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_d_min(self,_get_d_min(other));
	_set_d_max(self,_get_d_max(other));
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
VALUE _inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(_get_d_min(self),rb_intern("inspect"),0);
	array[3]=rb_funcall(_get_d_max(self),rb_intern("inspect"),0);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::Rectf* cother = wrap<CEGUI::Rectf*>(other);
	std::swap(_self->d_min,cother->d_min);
	std::swap(_self->d_max,cother->d_max);
	return self;
}
/*
*/
VALUE _plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Rectf>(other));
}
/*
*/
VALUE _mal(VALUE self,VALUE other)
{
	return wrap(*_self * NUM2DBL(other));
}
/*
*/
VALUE _isinside(VALUE self,VALUE point)
{
	return RBOOL(_self->isPointInRect(wrap<CEGUI::Vector2f>(point)));
}
/*
*/
VALUE _intersection(VALUE self,VALUE other)
{
	return wrap(_self->getIntersection(wrap<CEGUI::Rectf>(other)));
}
/*
*/
VALUE _constrainSize_self(VALUE self,VALUE size1,VALUE size2)
{
	_self->constrainSize(wrap<CEGUI::Sizef>(size1),wrap<CEGUI::Sizef>(size1));
	return self;
}
/*
*/
VALUE _constrainSizeMax_self(VALUE self,VALUE other)
{
	_self->constrainSizeMax(wrap<CEGUI::Sizef>(other));
	return self;
}
/*
*/
VALUE _constrainSizeMin_self(VALUE self,VALUE other)
{
	_self->constrainSizeMin(wrap<CEGUI::Sizef>(other));
	return self;
}
/*
*/
VALUE _constrainSize(VALUE self,VALUE size1,VALUE size2)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->constrainSize(wrap<CEGUI::Sizef>(size1),wrap<CEGUI::Sizef>(size1));
	return wrap(temp);
}
/*
*/
VALUE _constrainSizeMax(VALUE self,VALUE other)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->constrainSizeMax(wrap<CEGUI::Sizef>(other));
	return wrap(temp);
}
/*
*/
VALUE _constrainSizeMin(VALUE self,VALUE other)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->constrainSizeMin(wrap<CEGUI::Sizef>(other));
	return wrap(temp);
}



/*
*/
VALUE _offset_self(VALUE self,VALUE point)
{
	_self->offset(wrap<CEGUI::Vector2f>(point));
	return self;
}
/*
*/
VALUE _offset(VALUE self,VALUE point)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->offset(wrap<CEGUI::Vector2f>(point));
	return wrap(temp);
}


/*
 * call-seq:
 *   hash -> Integer
 * 
 * hash from the combined vector2 values.
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
 * packs a Rect into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_d_top(self));
	rb_ary_push(result,_get_d_bottom(self));
	rb_ary_push(result,_get_d_left(self));
	rb_ary_push(result,_get_d_right(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Rect.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	_set_d_right(self,rb_ary_pop(result));
	_set_d_left(self,rb_ary_pop(result));
	_set_d_bottom(self,rb_ary_pop(result));
	_set_d_top(self,rb_ary_pop(result));
	return self;
}

}
/*
 * Document-class: CEGUI::Rect
 * 
 * This class represents an Rect.
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
void Init_CeguiRect(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiRect,"top",1,1);
	rb_define_attr(rb_cCeguiRect,"left",1,1);
	rb_define_attr(rb_cCeguiRect,"bottom",1,1);
	rb_define_attr(rb_cCeguiRect,"right",1,1);

	rb_define_attr(rb_cCeguiRect,"min",1,1);
	rb_define_attr(rb_cCeguiRect,"max",1,1);
	
	rb_define_attr(rb_cCeguiRect,"position",1,1);
	rb_define_attr(rb_cCeguiRect,"height",1,1);
	rb_define_attr(rb_cCeguiRect,"width",1,1);
	rb_define_attr(rb_cCeguiRect,"size",1,1);
#endif

	using namespace CeguiRect;

	rb_cCeguiRect = rb_define_class_under(rb_mCegui,"Rect",rb_cObject);
	rb_define_alloc_func(rb_cCeguiRect,_alloc);
	rb_define_method(rb_cCeguiRect,"initialize",RUBY_METHOD_FUNC(_initialize),4);
	rb_define_private_method(rb_cCeguiRect,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);

	rb_define_attr_method(rb_cCeguiRect,"min",_get_d_min,_set_d_min);
	rb_define_attr_method(rb_cCeguiRect,"max",_get_d_max,_set_d_max);
	
	rb_define_attr_method(rb_cCeguiRect,"top",_get_d_top,_set_d_top);
	rb_define_attr_method(rb_cCeguiRect,"bottom",_get_d_bottom,_set_d_bottom);
	rb_define_attr_method(rb_cCeguiRect,"left",_get_d_left,_set_d_left);
	rb_define_attr_method(rb_cCeguiRect,"right",_get_d_left,_set_d_right);

	rb_define_attr_method(rb_cCeguiRect,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cCeguiRect,"height",_getHeight,_setHeight);
	rb_define_attr_method(rb_cCeguiRect,"width",_getWidth,_setWidth);
	rb_define_attr_method(rb_cCeguiRect,"size",_getSize,_setSize);
	
	rb_define_method(rb_cCeguiRect,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiRect,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiRect,"*",RUBY_METHOD_FUNC(_mal),1);

	rb_define_method(rb_cCeguiRect,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiRect,"swap",RUBY_METHOD_FUNC(_swap),1);

	rb_define_method(rb_cCeguiRect,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiRect,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);


	rb_define_method(rb_cCeguiRect,"constrainSize",RUBY_METHOD_FUNC(_constrainSize),2);
	rb_define_method(rb_cCeguiRect,"constrainSizeMin",RUBY_METHOD_FUNC(_constrainSizeMin),1);
	rb_define_method(rb_cCeguiRect,"constrainSizeMax",RUBY_METHOD_FUNC(_constrainSizeMax),1);
	rb_define_method(rb_cCeguiRect,"offset",RUBY_METHOD_FUNC(_offset),1);

	rb_define_method(rb_cCeguiRect,"constrainSize!",RUBY_METHOD_FUNC(_constrainSize_self),2);
	rb_define_method(rb_cCeguiRect,"constrainSizeMin!",RUBY_METHOD_FUNC(_constrainSizeMin_self),1);
	rb_define_method(rb_cCeguiRect,"constrainSizeMax!",RUBY_METHOD_FUNC(_constrainSizeMax_self),1);
	rb_define_method(rb_cCeguiRect,"offset!",RUBY_METHOD_FUNC(_offset_self),1);
}
