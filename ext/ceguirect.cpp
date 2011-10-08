
#include "ceguisize.hpp"
#include "ceguivector2.hpp"

#include "ceguirect.hpp"

#define _self wrap<CEGUI::Rectf*>(self)
VALUE rb_cCeguiRect;

macro_attr_prop(Rect,d_min,CEGUI::Vector2f)
macro_attr_prop(Rect,d_max,CEGUI::Vector2f)

macro_attr(Rect,Position,CEGUI::Vector2f)
macro_attr(Rect,Width,float)
macro_attr(Rect,Height,float)
macro_attr(Rect,Size,CEGUI::Sizef)

VALUE CeguiRect_alloc(VALUE self)
{
	return wrap(new CEGUI::Rectf());
}

VALUE CeguiRect_get_d_top(VALUE self)
{
	return wrap(_self->d_min.d_x);
}
VALUE CeguiRect_get_d_bottom(VALUE self)
{
	return wrap(_self->d_min.d_y);
}

VALUE CeguiRect_get_d_left(VALUE self)
{
	return wrap(_self->d_max.d_x);
}
VALUE CeguiRect_get_d_right(VALUE self)
{
	return wrap(_self->d_max.d_y);
}


VALUE CeguiRect_set_d_top(VALUE self,VALUE v)
{
	_self->d_min.d_x = wrap<float>(v);
	return v;
}
VALUE CeguiRect_set_d_bottom(VALUE self,VALUE v)
{
	_self->d_min.d_y = wrap<float>(v);
	return v;
}

VALUE CeguiRect_set_d_left(VALUE self,VALUE v)
{
	_self->d_max.d_x = wrap<float>(v);
	return v;
}
VALUE CeguiRect_set_d_right(VALUE self,VALUE v)
{
	_self->d_max.d_y = wrap<float>(v);
	return v;
}


/*
*/
VALUE CeguiRect_initialize(VALUE self,VALUE min,VALUE max)
{
	CeguiRect_set_d_min(self,min);
	CeguiRect_set_d_max(self,max);
	return self;
}
/*
*/
VALUE CeguiRect_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiRect_set_d_min(self,CeguiRect_get_d_min(other));
	CeguiRect_set_d_max(self,CeguiRect_get_d_max(other));
	return result;
}
/*
 * call-seq:
 *   vector2.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiRect_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(CeguiRect_get_d_min(self),rb_intern("inpect"),0);
	array[3]=rb_funcall(CeguiRect_get_d_max(self),rb_intern("inpect"),0);
	return rb_f_sprintf(4,array);
}/*
*/
VALUE CeguiRect_swap(VALUE self,VALUE other)
{
	CEGUI::Rectf* cother = wrap<CEGUI::Rectf*>(other);
	std::swap(_self->d_min,cother->d_min);
	std::swap(_self->d_max,cother->d_max);
	return self;
}
/*
*/
VALUE CeguiRect_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Rectf>(other));
}
/*
*/
VALUE CeguiRect_mal(VALUE self,VALUE other)
{
	return wrap(*_self * NUM2DBL(other));
}
/*
*/
VALUE CeguiRect_isinside(VALUE self,VALUE point)
{
	return RBOOL(_self->isPointInRect(wrap<CEGUI::Vector2f>(point)));
}
/*
*/
VALUE CeguiRect_intersection(VALUE self,VALUE other)
{
	return wrap(_self->getIntersection(wrap<CEGUI::Rectf>(other)));
}
/*
*/
VALUE CeguiRect_constrainSize_self(VALUE self,VALUE size1,VALUE size2)
{
	_self->constrainSize(wrap<CEGUI::Sizef>(size1),wrap<CEGUI::Sizef>(size1));
	return self;
}
/*
*/
VALUE CeguiRect_constrainSizeMax_self(VALUE self,VALUE other)
{
	_self->constrainSizeMax(wrap<CEGUI::Sizef>(other));
	return self;
}
/*
*/
VALUE CeguiRect_constrainSizeMin_self(VALUE self,VALUE other)
{
	_self->constrainSizeMin(wrap<CEGUI::Sizef>(other));
	return self;
}
/*
*/
VALUE CeguiRect_constrainSize(VALUE self,VALUE size1,VALUE size2)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->constrainSize(wrap<CEGUI::Sizef>(size1),wrap<CEGUI::Sizef>(size1));
	return wrap(temp);
}
/*
*/
VALUE CeguiRect_constrainSizeMax(VALUE self,VALUE other)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->constrainSizeMax(wrap<CEGUI::Sizef>(other));
	return wrap(temp);
}
/*
*/
VALUE CeguiRect_constrainSizeMin(VALUE self,VALUE other)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->constrainSizeMin(wrap<CEGUI::Sizef>(other));
	return wrap(temp);
}



/*
*/
VALUE CeguiRect_offset_self(VALUE self,VALUE point)
{
	_self->offset(wrap<CEGUI::Vector2f>(point));
	return self;
}
/*
*/
VALUE CeguiRect_offset(VALUE self,VALUE point)
{
	CEGUI::Rectf *temp = new CEGUI::Rectf(*_self);
	temp->offset(wrap<CEGUI::Vector2f>(point));
	return wrap(temp);
}


/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vector2 values.
 * ===Return value
 * Integer
*/
VALUE CeguiRect_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiRect_get_d_min(self));
	rb_ary_push(result,CeguiRect_get_d_max(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Rect into an string.
*/
VALUE CeguiRect_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiRect_get_d_top(self));
	rb_ary_push(result,CeguiRect_get_d_bottom(self));
	rb_ary_push(result,CeguiRect_get_d_left(self));
	rb_ary_push(result,CeguiRect_get_d_right(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Rect.
*/
VALUE CeguiRect_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	CeguiRect_set_d_right(self,rb_ary_pop(result));
	CeguiRect_set_d_left(self,rb_ary_pop(result));
	CeguiRect_set_d_bottom(self,rb_ary_pop(result));
	CeguiRect_set_d_top(self,rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::Rect
 * 
 * This class represents an Rect.
*/ 
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
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiRect,"top",1,1);
	rb_define_attr(rb_cCeguiRect,"left",1,1);
	rb_define_attr(rb_cCeguiRect,"bottom",1,1);
	rb_define_attr(rb_cCeguiRect,"right",1,1);
	
	rb_define_attr(rb_cCeguiRect,"position",1,1);
	rb_define_attr(rb_cCeguiRect,"height",1,1);
	rb_define_attr(rb_cCeguiRect,"width",1,1);
	rb_define_attr(rb_cCeguiRect,"size",1,1);
#endif
	rb_cCeguiRect = rb_define_class_under(rb_mCegui,"Rect",rb_cObject);
	rb_define_alloc_func(rb_cCeguiRect,CeguiRect_alloc);
	rb_define_method(rb_cCeguiRect,"initialize",RUBY_METHOD_FUNC(CeguiRect_initialize),4);
	rb_define_private_method(rb_cCeguiRect,"initialize_copy",RUBY_METHOD_FUNC(CeguiRect_initialize_copy),1);

	rb_define_attr_method(rb_cCeguiRect,"min",CeguiRect_get_d_min,CeguiRect_set_d_min);
	rb_define_attr_method(rb_cCeguiRect,"max",CeguiRect_get_d_max,CeguiRect_set_d_max);
	
	rb_define_attr_method(rb_cCeguiRect,"top",CeguiRect_get_d_top,CeguiRect_set_d_top);
	rb_define_attr_method(rb_cCeguiRect,"bottom",CeguiRect_get_d_bottom,CeguiRect_set_d_bottom);
	rb_define_attr_method(rb_cCeguiRect,"left",CeguiRect_get_d_left,CeguiRect_set_d_left);
	rb_define_attr_method(rb_cCeguiRect,"right",CeguiRect_get_d_left,CeguiRect_set_d_right);

	rb_define_attr_method(rb_cCeguiRect,"position",CeguiRect_getPosition,CeguiRect_setPosition);
	rb_define_attr_method(rb_cCeguiRect,"height",CeguiRect_getHeight,CeguiRect_setHeight);
	rb_define_attr_method(rb_cCeguiRect,"width",CeguiRect_getWidth,CeguiRect_setWidth);
	rb_define_attr_method(rb_cCeguiRect,"size",CeguiRect_getSize,CeguiRect_setSize);
	
	rb_define_method(rb_cCeguiRect,"inspect",RUBY_METHOD_FUNC(CeguiRect_inspect),0);

	rb_define_method(rb_cCeguiRect,"+",RUBY_METHOD_FUNC(CeguiRect_plus),1);
	rb_define_method(rb_cCeguiRect,"*",RUBY_METHOD_FUNC(CeguiRect_mal),1);

	rb_define_method(rb_cCeguiRect,"hash",RUBY_METHOD_FUNC(CeguiRect_hash),0);

	rb_define_method(rb_cCeguiRect,"swap",RUBY_METHOD_FUNC(CeguiRect_swap),1);

	rb_define_method(rb_cCeguiRect,"marshal_dump",RUBY_METHOD_FUNC(CeguiRect_marshal_dump),0);
	rb_define_method(rb_cCeguiRect,"marshal_load",RUBY_METHOD_FUNC(CeguiRect_marshal_load),1);


	rb_define_method(rb_cCeguiRect,"constrainSize",RUBY_METHOD_FUNC(CeguiRect_constrainSize),2);
	rb_define_method(rb_cCeguiRect,"constrainSizeMin",RUBY_METHOD_FUNC(CeguiRect_constrainSizeMin),1);
	rb_define_method(rb_cCeguiRect,"constrainSizeMax",RUBY_METHOD_FUNC(CeguiRect_constrainSizeMax),1);
	rb_define_method(rb_cCeguiRect,"offset",RUBY_METHOD_FUNC(CeguiRect_offset),1);

	rb_define_method(rb_cCeguiRect,"constrainSize!",RUBY_METHOD_FUNC(CeguiRect_constrainSize_self),2);
	rb_define_method(rb_cCeguiRect,"constrainSizeMin!",RUBY_METHOD_FUNC(CeguiRect_constrainSizeMin_self),1);
	rb_define_method(rb_cCeguiRect,"constrainSizeMax!",RUBY_METHOD_FUNC(CeguiRect_constrainSizeMax_self),1);
	rb_define_method(rb_cCeguiRect,"offset!",RUBY_METHOD_FUNC(CeguiRect_offset_self),1);
}
