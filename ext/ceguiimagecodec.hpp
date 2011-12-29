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
	return unwrapPtr<CEGUI::ImageCodec>(vcodec, rb_cCeguiImageCodec);
}
#endif /* __RubyCeguiImageCodec_H__ */
