#include "ceguiimagecodec.hpp"

#include "ceguiexception.hpp"
#include "ceguitexture.hpp"

#define _self wrap_imagecodec(self)

VALUE rb_cCeguiImageCodec;
/*
*/
VALUE CeguiImageCodec_getName(VALUE self)
{
	return wrap(_self.getIdentifierString());
}
/*
*/
VALUE CeguiImageCodec_getSupportedFormat(VALUE self)
{
	return wrap(_self.getSupportedFormat());
}

/*
*/
VALUE CeguiImageCodec_load(VALUE self,VALUE raw,VALUE texture)
{
  _self.load(wrap<CEGUI::RawDataContainer>(raw),wrap<CEGUI::Texture*>(texture));
  return self;
}
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiImageCodec_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s,%s>");
	array[1]=CeguiImageCodec_getName(self);
	array[2]=CeguiImageCodec_getSupportedFormat(self);
	return rb_f_sprintf(3,array);
}


/*
*/
void Init_CeguiImageCodec(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiImageCodec = rb_define_class_under(rb_mCegui,"ImageCodec",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiImageCodec);

	rb_define_method(rb_cCeguiImageCodec,"name",RUBY_METHOD_FUNC(CeguiImageCodec_getName),0);
	rb_define_method(rb_cCeguiImageCodec,"supportedFormat",RUBY_METHOD_FUNC(CeguiImageCodec_getSupportedFormat),0);
	rb_define_method(rb_cCeguiImageCodec,"inspect",RUBY_METHOD_FUNC(CeguiImageCodec_inspect),0);
	
	rb_define_method(rb_cCeguiImageCodec,"load",RUBY_METHOD_FUNC(CeguiImageCodec_load),2);
}
