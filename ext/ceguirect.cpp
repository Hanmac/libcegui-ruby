#include "ceguirect.hpp"
#include "ceguisize.hpp"
#include "ceguivector2.hpp"
#define _self wrap<CEGUI::Rect*>(self)
VALUE rb_cCeguiRect;

VALUE CeguiRect_alloc(VALUE self)
{
	return wrap(new CEGUI::Rect);
}
macro_attr_prop_with_func(Rect,d_top,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Rect,d_bottom,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Rect,d_left,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Rect,d_right,DBL2NUM,NUM2DBL)

macro_attr(Rect,Position,CEGUI::Vector2)
macro_attr_with_func(Rect,Width,DBL2NUM,NUM2DBL)
macro_attr_with_func(Rect,Height,DBL2NUM,NUM2DBL)
macro_attr(Rect,Size,CEGUI::Size)


/*
*/
VALUE CeguiRect_initialize(VALUE self,VALUE top,VALUE bottom,VALUE left,VALUE right)
{
	CeguiRect_set_d_top(self,top);
	CeguiRect_set_d_bottom(self,bottom);
	CeguiRect_set_d_left(self,left);
	CeguiRect_set_d_right(self,right);
	return self;
}
/*
*/
VALUE CeguiRect_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiRect_set_d_top(self,CeguiRect_get_d_top(other));
	CeguiRect_set_d_bottom(self,CeguiRect_get_d_bottom(other));
	CeguiRect_set_d_left(self,CeguiRect_get_d_left(other));
	CeguiRect_set_d_right(self,CeguiRect_get_d_right(other));
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
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiRect_get_d_top(self);
	array[3]=CeguiRect_get_d_bottom(self);
	array[4]=CeguiRect_get_d_left(self);
	array[5]=CeguiRect_get_d_right(self);
	return rb_f_sprintf(6,array);
}/*
*/
VALUE CeguiRect_swap(VALUE self,VALUE other)
{
	CEGUI::Rect* cother = wrap<CEGUI::Rect*>(other);
	std::swap(_self->d_top,cother->d_top);
	std::swap(_self->d_bottom,cother->d_bottom);
	std::swap(_self->d_left,cother->d_left);
	std::swap(_self->d_right,cother->d_right);
	return self;
}
/*
*/
VALUE CeguiRect_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::Rect>(other));
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
	return RBOOL(_self->isPointInRect(wrap<CEGUI::Vector2>(point)));
}
/*
*/
VALUE CeguiRect_intersection(VALUE self,VALUE other)
{
	return wrap(_self->getIntersection(wrap<CEGUI::Rect>(other)));
}
/*
*/
VALUE CeguiRect_constrainSize_self(VALUE self,VALUE size1,VALUE size2)
{
	_self->constrainSize(wrap<CEGUI::Size>(size1),wrap<CEGUI::Size>(size1));
	return self;
}
/*
*/
VALUE CeguiRect_constrainSizeMax_self(VALUE self,VALUE other)
{
	_self->constrainSizeMax(wrap<CEGUI::Size>(other));
	return self;
}
/*
*/
VALUE CeguiRect_constrainSizeMin_self(VALUE self,VALUE other)
{
	_self->constrainSizeMin(wrap<CEGUI::Size>(other));
	return self;
}
/*
*/
VALUE CeguiRect_constrainSize(VALUE self,VALUE size1,VALUE size2)
{
	CEGUI::Rect *temp = new CEGUI::Rect(*_self);
	temp->constrainSize(wrap<CEGUI::Size>(size1),wrap<CEGUI::Size>(size1));
	return wrap(temp);
}
/*
*/
VALUE CeguiRect_constrainSizeMax(VALUE self,VALUE other)
{
	CEGUI::Rect *temp = new CEGUI::Rect(*_self);
	temp->constrainSizeMax(wrap<CEGUI::Size>(other));
	return wrap(temp);
}
/*
*/
VALUE CeguiRect_constrainSizeMin(VALUE self,VALUE other)
{
	CEGUI::Rect *temp = new CEGUI::Rect(*_self);
	temp->constrainSizeMin(wrap<CEGUI::Size>(other));
	return wrap(temp);
}



/*
*/
VALUE CeguiRect_offset_self(VALUE self,VALUE point)
{
	_self->offset(wrap<CEGUI::Vector2>(point));
	return self;
}
/*
*/
VALUE CeguiRect_offset(VALUE self,VALUE point)
{
	CEGUI::Rect *temp = new CEGUI::Rect(*_self);
	temp->offset(wrap<CEGUI::Vector2>(point));
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
	rb_ary_push(result,CeguiRect_get_d_top(self));
	rb_ary_push(result,CeguiRect_get_d_bottom(self));
	rb_ary_push(result,CeguiRect_get_d_left(self));
	rb_ary_push(result,CeguiRect_get_d_right(self));
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
