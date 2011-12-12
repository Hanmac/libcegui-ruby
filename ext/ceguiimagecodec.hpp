#ifndef __RubyCeguiImageCodec_H__
#define __RubyCeguiImageCodec_H__

#include "main.hpp"
void Init_CeguiImageCodec(VALUE rb_mCegui);
extern VALUE rb_cCeguiImageCodec;

inline VALUE wrap(CEGUI::ImageCodec &codec )
{
	return Data_Wrap_Struct(rb_cCeguiImageCodec, NULL, NULL, &codec);
}
template<>
inline CEGUI::ImageCodec* wrap<CEGUI::ImageCodec*>(const VALUE &vcodec)
{
	if (rb_obj_is_kind_of(vcodec, rb_cCeguiImageCodec)){
		CEGUI::ImageCodec *codec;
		Data_Get_Struct( vcodec, CEGUI::ImageCodec, codec);
		return codec;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiImageCodec),rb_obj_classname(vcodec));
	}
}
#endif /* __RubyCeguiImageCodec_H__ */
