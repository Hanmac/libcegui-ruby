#include "ceguiproperty.hpp"
#define _self wrap<CEGUI::Property*>(self)
VALUE rb_cCeguiProperty;
/*
*/
VALUE CeguiProperty_getName(VALUE self)
{
	return wrap(_self->getName());
}


/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiProperty_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=CeguiProperty_getName(self);
	return rb_f_sprintf(3,array);
}


void Init_CeguiProperty(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
#endif
	rb_cCeguiProperty = rb_define_class_under(rb_mCegui,"Property",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiProperty);
	
	rb_define_method(rb_cCeguiProperty,"inspect",RUBY_METHOD_FUNC(CeguiProperty_inspect),0);
	rb_define_method(rb_cCeguiProperty,"name",RUBY_METHOD_FUNC(CeguiProperty_getName),0);
}
