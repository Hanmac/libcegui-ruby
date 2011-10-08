#include "ceguiuvector2.hpp"
#include "ceguiubox.hpp"
#define _self wrap<CEGUI::UBox*>(self)
VALUE rb_cCeguiUBox;

VALUE CeguiUBox_alloc(VALUE self)
{
	return wrap(new CEGUI::UBox);
}
macro_attr_prop(UBox,d_top,CEGUI::UDim)
macro_attr_prop(UBox,d_left,CEGUI::UDim)
macro_attr_prop(UBox,d_bottom,CEGUI::UDim)
macro_attr_prop(UBox,d_right,CEGUI::UDim)
/*
*/
VALUE CeguiUBox_initialize(VALUE self,VALUE top,VALUE left,VALUE bottom,VALUE right)
{
	CeguiUBox_set_d_top(self,top);
	CeguiUBox_set_d_left(self,left);
	CeguiUBox_set_d_bottom(self,bottom);
	CeguiUBox_set_d_right(self,right);
	return self;
}
/*
*/
VALUE CeguiUBox_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiUBox_set_d_top(self,CeguiUBox_get_d_top(other));
	CeguiUBox_set_d_left(self,CeguiUBox_get_d_left(other));
	CeguiUBox_set_d_bottom(self,CeguiUBox_get_d_bottom(other));
	CeguiUBox_set_d_right(self,CeguiUBox_get_d_right(other));
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
VALUE CeguiUBox_inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%s, %s, %s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=rb_funcall(CeguiUBox_get_d_top(self),rb_intern("inpect"),0);
	array[3]=rb_funcall(CeguiUBox_get_d_left(self),rb_intern("inpect"),0);
	array[4]=rb_funcall(CeguiUBox_get_d_bottom(self),rb_intern("inpect"),0);
	array[5]=rb_funcall(CeguiUBox_get_d_right(self),rb_intern("inpect"),0);
	return rb_f_sprintf(6,array);
}
/*
*/
VALUE CeguiUBox_swap(VALUE self,VALUE other)
{
	CEGUI::UBox* cother = wrap<CEGUI::UBox*>(other);
	std::swap(_self->d_top,cother->d_top);
	std::swap(_self->d_left,cother->d_left);
	std::swap(_self->d_bottom,cother->d_bottom);
	std::swap(_self->d_right,cother->d_right);
	return self;
}
/*
*/
VALUE CeguiUBox_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::UBox>(other));
}
/*
*/
VALUE CeguiUBox_mal(VALUE self,VALUE other)
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
VALUE CeguiUBox_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiUBox_get_d_top(self));
	rb_ary_push(result,CeguiUBox_get_d_left(self));
	rb_ary_push(result,CeguiUBox_get_d_bottom(self));
	rb_ary_push(result,CeguiUBox_get_d_right(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a UBox into an string.
*/
VALUE CeguiUBox_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(_self->d_top.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_top.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_left.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_left.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_bottom.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_bottom.d_offset));
	rb_ary_push(result,DBL2NUM(_self->d_right.d_scale));
	rb_ary_push(result,DBL2NUM(_self->d_right.d_offset));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddddddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an UBox.
*/
VALUE CeguiUBox_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddddddd"));
	_self->d_right.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_right.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_bottom.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_bottom.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_left.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_left.d_scale=NUM2DBL(rb_ary_pop(result));
	_self->d_top.d_offset=NUM2DBL(rb_ary_pop(result));
	_self->d_top.d_scale=NUM2DBL(rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::UBox
 * 
 * 
*/ 
/* Document-attr: top
 * the top Cordinate */
/* Document-attr: left
 * the left Cordinate */
/* Document-attr: bottom
 * the bottom Cordinate */
/* Document-attr: right
 * the right Cordinate */
void Init_CeguiUBox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiUBox,"top",1,1);
	rb_define_attr(rb_cCeguiUBox,"left",1,1);
	rb_define_attr(rb_cCeguiUBox,"bottom",1,1);
	rb_define_attr(rb_cCeguiUBox,"right",1,1);
#endif
	rb_cCeguiUBox = rb_define_class_under(rb_mCegui,"UDim",rb_cObject);
	rb_define_alloc_func(rb_cCeguiUBox,CeguiUBox_alloc);
	rb_define_method(rb_cCeguiUBox,"initialize",RUBY_METHOD_FUNC(CeguiUBox_initialize),2);
	rb_define_private_method(rb_cCeguiUBox,"initialize_copy",RUBY_METHOD_FUNC(CeguiUBox_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiUBox,"top",CeguiUBox_get_d_top,CeguiUBox_set_d_top);
	rb_define_attr_method(rb_cCeguiUBox,"left",CeguiUBox_get_d_left,CeguiUBox_set_d_left);
	rb_define_attr_method(rb_cCeguiUBox,"bottom",CeguiUBox_get_d_bottom,CeguiUBox_set_d_bottom);
	rb_define_attr_method(rb_cCeguiUBox,"right",CeguiUBox_get_d_right,CeguiUBox_set_d_right);

	rb_define_method(rb_cCeguiUBox,"inspect",RUBY_METHOD_FUNC(CeguiUBox_inspect),0);

	rb_define_method(rb_cCeguiUBox,"+",RUBY_METHOD_FUNC(CeguiUBox_plus),1);
	rb_define_method(rb_cCeguiUBox,"*",RUBY_METHOD_FUNC(CeguiUBox_mal),1);

	rb_define_method(rb_cCeguiUBox,"hash",RUBY_METHOD_FUNC(CeguiUBox_hash),0);

	rb_define_method(rb_cCeguiUBox,"swap",RUBY_METHOD_FUNC(CeguiUBox_swap),1);

	rb_define_method(rb_cCeguiUBox,"marshal_dump",RUBY_METHOD_FUNC(CeguiUBox_marshal_dump),0);
	rb_define_method(rb_cCeguiUBox,"marshal_load",RUBY_METHOD_FUNC(CeguiUBox_marshal_load),1);

}
