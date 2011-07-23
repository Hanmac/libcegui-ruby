#include "ceguiimagecodec.hpp"

#include "ceguiexception.hpp"
#include "ceguitexture.hpp"

#define _self wrap<CEGUI::ImageCodec*>(self)

VALUE rb_cCeguiImageCodec;

#ifdef HAVE_IMAGECODECMODULES_DEVILIMAGECODEC_CEGUIDEVILIMAGECODEC_H
VALUE rb_cCeguiDevILImageCodec;
VALUE CeguiDevILImageCodec_alloc(VALUE self)
{return wrap(new CEGUI::DevILImageCodec());}
#endif

#ifdef HAVE_IMAGECODECMODULES_FREEIMAGEIMAGECODEC_CEGUIFREEIMAGEIMAGECODEC_H
VALUE rb_cCeguiFreeImageImageCodec;
VALUE CeguiFreeImageImageCodec_alloc(VALUE self)
{return wrap(new CEGUI::FreeImageImageCodec());}
#endif

#ifdef HAVE_IMAGECODECMODULES_SILLYIMAGECODEC_CEGUISILLYIMAGECODEC_H
VALUE rb_cCeguiSILLYImageCodec;
VALUE CeguiSILLYImageCodec_alloc(VALUE self)
{return wrap(new CEGUI::SILLYImageCodec());}
#endif

#ifdef HAVE_IMAGECODECMODULES_STBIMAGECODEC_CEGUISTBIMAGECODEC_H
VALUE rb_cCeguiSTBImageCodec;
VALUE CeguiSTBImageCodec_alloc(VALUE self)
{return wrap(new CEGUI::STBImageCodec());}
#endif

#ifdef HAVE_IMAGECODECMODULES_TGAIMAGECODEC_CEGUITGAIMAGECODEC_H
VALUE rb_cCeguiTGAImageCodec;
VALUE CeguiTGAImageCodec_alloc(VALUE self)
{return wrap(new CEGUI::TGAImageCodec());}
#endif

/*
*/
VALUE CeguiImageCodec_getName(VALUE self)
{
	return wrap(_self->getIdentifierString());
}
/*
*/
VALUE CeguiImageCodec_getSupportedFormat(VALUE self)
{
	return wrap(_self->getSupportedFormat());
}

/*
*/
VALUE CeguiImageCodec_load(VALUE self,VALUE raw,VALUE texture)
{
  _self->load(wrap<CEGUI::RawDataContainer>(raw),wrap<CEGUI::Texture*>(texture));
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
	
#ifdef HAVE_IMAGECODECMODULES_DEVILIMAGECODEC_CEGUIDEVILIMAGECODEC_H
	rb_cCeguiDevILImageCodec = rb_define_class_under(rb_mCegui,"DevILImageCodec",rb_cCeguiImageCodec);
	rb_define_alloc_func(rb_cCeguiDevILImageCodec,CeguiDevILImageCodec_alloc);
#endif

#ifdef HAVE_IMAGECODECMODULES_FREEIMAGEIMAGECODEC_CEGUIFREEIMAGEIMAGECODEC_H
	rb_cCeguiFreeImageImageCodec = rb_define_class_under(rb_mCegui,"FreeImageImageCodec",rb_cCeguiImageCodec);
	rb_define_alloc_func(rb_cCeguiFreeImageImageCodec,CeguiFreeImageImageCodec_alloc);
#endif

#ifdef HAVE_IMAGECODECMODULES_SILLYIMAGECODEC_CEGUISILLYIMAGECODEC_H
	rb_cCeguiSILLYImageCodec = rb_define_class_under(rb_mCegui,"SILLYImageCodec",rb_cCeguiImageCodec);
	rb_define_alloc_func(rb_cCeguiSILLYImageCodec,CeguiSILLYImageCodec_alloc);
#endif

#ifdef HAVE_IMAGECODECMODULES_STBIMAGECODEC_CEGUISTBIMAGECODEC_H
	rb_cCeguiSTBImageCodec = rb_define_class_under(rb_mCegui,"STBImageCodec",rb_cCeguiImageCodec);
	rb_define_alloc_func(rb_cCeguiSTBImageCodec,CeguiSTBImageCodec_alloc);
#endif

#ifdef HAVE_IMAGECODECMODULES_TGAIMAGECODEC_CEGUITGAIMAGECODEC_H
	rb_cCeguiTGAImageCodec = rb_define_class_under(rb_mCegui,"TGAImageCodec",rb_cCeguiImageCodec);
	rb_define_alloc_func(rb_cCeguiTGAImageCodec,CeguiTGAImageCodec_alloc);
#endif
}
