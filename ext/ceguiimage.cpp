#include "ceguiimage.hpp"
#include "ceguixmlserializer.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Image*>(self)

VALUE rb_cCeguiImage;

/*
*/
VALUE CeguiImage_getName(VALUE self)
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
VALUE CeguiImage_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=CeguiImage_getName(self);
	return rb_f_sprintf(3,array);
}
/*
*/
VALUE CeguiImage_writeXML(VALUE self,VALUE xml)
{
	CEGUI::XMLSerializer *temp =wrap<CEGUI::XMLSerializer*>(xml);
	_self->writeXMLToStream(*temp);
	return self;
}

/*
*/
void Init_CeguiImage(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiImage = rb_define_class_under(rb_mCegui,"Image",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiImage);

	rb_define_method(rb_cCeguiImage,"name",RUBY_METHOD_FUNC(CeguiImage_getName),0);
	rb_define_method(rb_cCeguiImage,"inspect",RUBY_METHOD_FUNC(CeguiImage_inspect),0);

	rb_define_method(rb_cCeguiImage,"writeXML",RUBY_METHOD_FUNC(CeguiImage_writeXML),1);
}
