#include "ceguiudim.hpp"
#define _self wrap<CEGUI::UDim*>(self)
VALUE rb_cCeguiUDim;

VALUE CeguiUDim_alloc(VALUE self)
{
	return wrap(new CEGUI::UDim(0,0));
}
macro_attr_prop(UDim,d_scale,float)
macro_attr_prop(UDim,d_offset,float)
/*
*/
VALUE CeguiUDim_initialize(VALUE self,VALUE scale,VALUE offset)
{
	CeguiUDim_set_d_scale(self,scale);
	CeguiUDim_set_d_offset(self,offset);
	return self;
}
/*
*/
VALUE CeguiUDim_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiUDim_set_d_scale(self,CeguiUDim_get_d_scale(other));
	CeguiUDim_set_d_offset(self,CeguiUDim_get_d_offset(other));
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
VALUE CeguiUDim_inspect(VALUE self)
{
	VALUE array[4];
	array[0]=rb_str_new2("#<%s:(%f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiUDim_get_d_scale(self);
	array[3]=CeguiUDim_get_d_offset(self);
	return rb_f_sprintf(4,array);
}
/*
*/
VALUE CeguiUDim_minusself(VALUE self)
{
	return wrap(CEGUI::UDim(- _self->d_scale,- _self->d_offset));
}
/*
*/
VALUE CeguiUDim_swap(VALUE self,VALUE other)
{
	CEGUI::UDim* cother = wrap<CEGUI::UDim*>(other);
	std::swap(_self->d_scale,cother->d_scale);
	std::swap(_self->d_offset,cother->d_offset);
	return self;
}
/*
*/
VALUE CeguiUDim_plus(VALUE self,VALUE other)
{
	return wrap(*_self + wrap<CEGUI::UDim>(other));
}
/*
*/
VALUE CeguiUDim_minus(VALUE self,VALUE other)
{
	return wrap(*_self - wrap<CEGUI::UDim>(other));
}
/*
*/
VALUE CeguiUDim_mal(VALUE self,VALUE other)
{
	return wrap(*_self * wrap<CEGUI::UDim>(other));
}
/*
*/
VALUE CeguiUDim_durch(VALUE self,VALUE other)
{
	return wrap(*_self / wrap<CEGUI::UDim>(other));
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined udim values.
 * ===Return value
 * Integer
*/
VALUE CeguiUDim_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiUDim_get_d_scale(self));
	rb_ary_push(result,CeguiUDim_get_d_offset(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a UDim into an string.
*/
VALUE CeguiUDim_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiUDim_get_d_scale(self));
	rb_ary_push(result,CeguiUDim_get_d_offset(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an UDim.
*/
VALUE CeguiUDim_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dd"));
	CeguiUDim_set_d_offset(self,rb_ary_pop(result));
	CeguiUDim_set_d_scale(self,rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::UDim
 * 
 * 
*/ 
/* Document-attr: scale
 * the scale Cordinate */
/* Document-attr: offset
 * the offset Cordinate */
void Init_CeguiUDim(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiUDim,"scale",1,1);
	rb_define_attr(rb_cCeguiUDim,"offset",1,1);
#endif
	rb_cCeguiUDim = rb_define_class_under(rb_mCegui,"UDim",rb_cObject);
	rb_define_alloc_func(rb_cCeguiUDim,CeguiUDim_alloc);
	rb_define_method(rb_cCeguiUDim,"initialize",RUBY_METHOD_FUNC(CeguiUDim_initialize),2);
	rb_define_private_method(rb_cCeguiUDim,"initialize_copy",RUBY_METHOD_FUNC(CeguiUDim_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiUDim,"scale",CeguiUDim_get_d_scale,CeguiUDim_set_d_scale);
	rb_define_attr_method(rb_cCeguiUDim,"offset",CeguiUDim_get_d_offset,CeguiUDim_set_d_offset);

	rb_define_method(rb_cCeguiUDim,"inspect",RUBY_METHOD_FUNC(CeguiUDim_inspect),0);

	rb_define_method(rb_cCeguiUDim,"-@",RUBY_METHOD_FUNC(CeguiUDim_minusself),0);

	rb_define_method(rb_cCeguiUDim,"+",RUBY_METHOD_FUNC(CeguiUDim_plus),1);
	rb_define_method(rb_cCeguiUDim,"-",RUBY_METHOD_FUNC(CeguiUDim_minus),1);
	rb_define_method(rb_cCeguiUDim,"*",RUBY_METHOD_FUNC(CeguiUDim_mal),1);
	rb_define_method(rb_cCeguiUDim,"/",RUBY_METHOD_FUNC(CeguiUDim_durch),1);

	rb_define_method(rb_cCeguiUDim,"hash",RUBY_METHOD_FUNC(CeguiUDim_hash),0);

	rb_define_method(rb_cCeguiUDim,"swap",RUBY_METHOD_FUNC(CeguiUDim_swap),1);

	rb_define_method(rb_cCeguiUDim,"marshal_dump",RUBY_METHOD_FUNC(CeguiUDim_marshal_dump),0);
	rb_define_method(rb_cCeguiUDim,"marshal_load",RUBY_METHOD_FUNC(CeguiUDim_marshal_load),1);

}
