#ifndef __RubyCeguiImageCodec_H__
#define __RubyCeguiImageCodec_H__

#include "main.hpp"
void Init_CeguiImageCodec(VALUE rb_mCegui);
extern VALUE rb_cCeguiImageCodec;




#ifdef HAVE_IMAGECODECMODULES_DEVILIMAGECODEC_CEGUIDEVILIMAGECODEC_H
#include <ImageCodecModules/DevILImageCodec/CEGUIDevILImageCodec.h>
extern VALUE rb_cCeguiDevILImageCodec;
template <>
inline VALUE wrap< CEGUI::DevILImageCodec >(CEGUI::DevILImageCodec *codec )
{
	if(codec==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiDevILImageCodec, NULL, NULL, codec);
}
#endif

#ifdef HAVE_IMAGECODECMODULES_FREEIMAGEIMAGECODEC_CEGUIFREEIMAGEIMAGECODEC_H
#include <ImageCodecModules/FreeImageImageCodec/CEGUIFreeImageImageCodec.h>
extern VALUE rb_cCeguiFreeImageImageCodec;
template <>
inline VALUE wrap< CEGUI::FreeImageImageCodec >(CEGUI::FreeImageImageCodec *codec )
{
	if(codec==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiFreeImageImageCodec, NULL, NULL, codec);
}
#endif

#ifdef HAVE_IMAGECODECMODULES_SILLYIMAGECODEC_CEGUISILLYIMAGECODEC_H
#include <ImageCodecModules/SILLYImageCodec/CEGUISILLYImageCodec.h>
extern VALUE rb_cCeguiSILLYImageCodec;
template <>
inline VALUE wrap< CEGUI::SILLYImageCodec >(CEGUI::SILLYImageCodec *codec )
{
	if(codec==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiSILLYImageCodec, NULL, NULL, codec);
}
#endif


#ifdef HAVE_IMAGECODECMODULES_STBIMAGECODEC_CEGUISTBIMAGECODEC_H
#include <ImageCodecModules/STBImageCodec/CEGUISTBImageCodec.h>
extern VALUE rb_cCeguiSTBImageCodec;
template <>
inline VALUE wrap< CEGUI::STBImageCodec >(CEGUI::STBImageCodec *codec )
{
	if(codec==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiSTBImageCodec, NULL, NULL, codec);
}
#endif


#ifdef HAVE_IMAGECODECMODULES_TGAIMAGECODEC_CEGUITGAIMAGECODEC_H
#include <ImageCodecModules/TGAImageCodec/CEGUITGAImageCodec.h>
extern VALUE rb_cCeguiTGAImageCodec;
template <>
inline VALUE wrap< CEGUI::TGAImageCodec >(CEGUI::TGAImageCodec *codec )
{
	if(codec==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiTGAImageCodec, NULL, NULL, codec);
}
#endif


template <>
inline VALUE wrap< CEGUI::ImageCodec >(CEGUI::ImageCodec *codec )
{
	if(codec==NULL)
		return Qnil;
#ifdef HAVE_IMAGECODECMODULES_DEVILIMAGECODEC_CEGUIDEVILIMAGECODEC_H
	CEGUI::DevILImageCodec *devilimagecodec = dynamic_cast<CEGUI::DevILImageCodec*>(codec);
	if(devilimagecodec)
		return wrap(devilimagecodec);
#endif
#ifdef HAVE_IMAGECODECMODULES_FREEIMAGEIMAGECODEC_CEGUIFREEIMAGEIMAGECODEC_H
	CEGUI::FreeImageImageCodec *freeimageimagecodec = dynamic_cast<CEGUI::FreeImageImageCodec*>(codec);
	if(freeimageimagecodec)
		return wrap(freeimageimagecodec);
#endif
#ifdef HAVE_IMAGECODECMODULES_SILLYIMAGECODEC_CEGUISILLYIMAGECODEC_H
	CEGUI::SILLYImageCodec *sillyimagecodec = dynamic_cast<CEGUI::SILLYImageCodec*>(codec);
	if(sillyimagecodec)
		return wrap(sillyimagecodec);
#endif
#ifdef HAVE_IMAGECODECMODULES_STBIMAGECODEC_CEGUISTBIMAGECODEC_H
	CEGUI::STBImageCodec *stbimagecodec = dynamic_cast<CEGUI::STBImageCodec*>(codec);
	if(stbimagecodec)
		return wrap(stbimagecodec);
#endif
#ifdef HAVE_IMAGECODECMODULES_TGAIMAGECODEC_CEGUITGAIMAGECODEC_H
	CEGUI::TGAImageCodec *tgaimagecodec = dynamic_cast<CEGUI::TGAImageCodec*>(codec);
	if(tgaimagecodec)
		return wrap(tgaimagecodec);
#endif
	return Data_Wrap_Struct(rb_cCeguiImageCodec, NULL, NULL, codec);
}
template <>
inline CEGUI::ImageCodec* wrap< CEGUI::ImageCodec* >(const VALUE &vcodec)
{
	if (rb_obj_is_kind_of(vcodec, rb_cCeguiImageCodec)){
		CEGUI::ImageCodec *codec;
		Data_Get_Struct( vcodec, CEGUI::ImageCodec, codec);
		return codec;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiImageCodec),rb_obj_classname(vcodec));
		return NULL;
	}
}
#endif /* __RubyCeguiImageCodec_H__ */
