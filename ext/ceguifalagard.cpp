#include "ceguifalagard.hpp"
#include "ceguiwindow.hpp"
#define _self wrap<CEGUI::WindowFactoryManager::FalagardWindowMapping*>(self)
VALUE rb_cCeguiFalagard;

VALUE CeguiFalagard_alloc(VALUE self)
{
	return wrap(new CEGUI::WindowFactoryManager::FalagardWindowMapping);
}
macro_attr_prop(Falagard,d_windowType,CEGUI::String)
macro_attr_prop(Falagard,d_lookName,CEGUI::String)
macro_attr_prop(Falagard,d_baseType,CEGUI::String)
macro_attr_prop(Falagard,d_rendererType,CEGUI::String)
macro_attr_prop(Falagard,d_effectName,CEGUI::String)
/*
*/
VALUE CeguiFalagard_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiFalagard_set_d_windowType(self,CeguiFalagard_get_d_windowType(other));
	CeguiFalagard_set_d_lookName(self,CeguiFalagard_get_d_lookName(other));
	CeguiFalagard_set_d_baseType(self,CeguiFalagard_get_d_baseType(other));
	CeguiFalagard_set_d_rendererType(self,CeguiFalagard_get_d_rendererType(other));
	CeguiFalagard_set_d_effectName(self,CeguiFalagard_get_d_effectName(other));
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
VALUE CeguiFalagard_inspect(VALUE self)
{
	VALUE array[7];
	array[0]=rb_str_new2("#<%s:(%s, %s, %s, %s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiFalagard_get_d_windowType(self);
	array[3]=CeguiFalagard_get_d_lookName(self);
	array[4]=CeguiFalagard_get_d_baseType(self);
	array[5]=CeguiFalagard_get_d_rendererType(self);
	array[6]=CeguiFalagard_get_d_effectName(self);
	return rb_f_sprintf(7,array);
}
/*
 * call-seq:
 *   hash -> Integer
 * 
 * hash from the combined values.
 * ===Return value
 * Integer
*/
VALUE CeguiFalagard_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiFalagard_get_d_windowType(self));
	rb_ary_push(result,CeguiFalagard_get_d_lookName(self));
	rb_ary_push(result,CeguiFalagard_get_d_baseType(self));
	rb_ary_push(result,CeguiFalagard_get_d_rendererType(self));
	rb_ary_push(result,CeguiFalagard_get_d_effectName(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Falagard into an string.
*/
VALUE CeguiFalagard_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiFalagard_get_d_windowType(self));
	rb_ary_push(result,CeguiFalagard_get_d_lookName(self));
	rb_ary_push(result,CeguiFalagard_get_d_baseType(self));
	rb_ary_push(result,CeguiFalagard_get_d_rendererType(self));
	rb_ary_push(result,CeguiFalagard_get_d_effectName(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("ppppp"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Falagard.
*/
VALUE CeguiFalagard_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("ppppp"));
	CeguiFalagard_set_d_effectName(self,rb_ary_pop(result));
	CeguiFalagard_set_d_rendererType(self,rb_ary_pop(result));
	CeguiFalagard_set_d_baseType(self,rb_ary_pop(result));
	CeguiFalagard_set_d_lookName(self,rb_ary_pop(result));
	CeguiFalagard_set_d_windowType(self,rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::Window::Falagard
 * 
 * 
*/ 
void Init_CeguiFalagard(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiFalagard,"windowType",1,1);
	rb_define_attr(rb_cCeguiFalagard,"lookType",1,1);
	rb_define_attr(rb_cCeguiFalagard,"baseType",1,1);
	rb_define_attr(rb_cCeguiFalagard,"rendererType",1,1);
	rb_define_attr(rb_cCeguiFalagard,"effectName",1,1);
	
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
#endif
	rb_cCeguiFalagard = rb_define_class_under(rb_cCeguiWindow,"Falagard",rb_cObject);
	rb_define_alloc_func(rb_cCeguiFalagard,CeguiFalagard_alloc);
	rb_define_private_method(rb_cCeguiFalagard,"initialize_copy",RUBY_METHOD_FUNC(CeguiFalagard_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiFalagard,"windowType",CeguiFalagard_get_d_windowType,CeguiFalagard_set_d_windowType);
	rb_define_attr_method(rb_cCeguiFalagard,"lookName",CeguiFalagard_get_d_lookName,CeguiFalagard_set_d_lookName);
	rb_define_attr_method(rb_cCeguiFalagard,"baseType",CeguiFalagard_get_d_baseType,CeguiFalagard_set_d_baseType);
	rb_define_attr_method(rb_cCeguiFalagard,"rendererType",CeguiFalagard_get_d_rendererType,CeguiFalagard_set_d_rendererType);
	rb_define_attr_method(rb_cCeguiFalagard,"effectName",CeguiFalagard_get_d_effectName,CeguiFalagard_set_d_effectName);

	rb_define_method(rb_cCeguiFalagard,"inspect",RUBY_METHOD_FUNC(CeguiFalagard_inspect),0);

	rb_define_method(rb_cCeguiFalagard,"hash",RUBY_METHOD_FUNC(CeguiFalagard_hash),0);

//	rb_define_method(rb_cCeguiFalagard,"swap",RUBY_METHOD_FUNC(CeguiFalagard_swap),1);

	rb_define_method(rb_cCeguiFalagard,"marshal_dump",RUBY_METHOD_FUNC(CeguiFalagard_marshal_dump),0);
	rb_define_method(rb_cCeguiFalagard,"marshal_load",RUBY_METHOD_FUNC(CeguiFalagard_marshal_load),1);

}
