#ifndef __RubyCeguiImageCodec_H__
#define __RubyCeguiImageCodec_H__

#include "main.hpp"
void Init_CeguiImageCodec(VALUE rb_mCegui);
extern VALUE rb_cCeguiImageCodec;

class ruby_imagecodec{
public:
ruby_imagecodec(CEGUI::ImageCodec& c) : codec(c){};
	CEGUI::ImageCodec& codec;

};

inline VALUE wrap_imagecodec(CEGUI::ImageCodec &codec )
{
	ruby_imagecodec *temp = new ruby_imagecodec(codec);
	return Data_Wrap_Struct(rb_cCeguiImageCodec, NULL, NULL, temp);
}

inline CEGUI::ImageCodec& wrap_imagecodec(const VALUE &vcodec)
{
	if (rb_obj_is_kind_of(vcodec, rb_cCeguiImageCodec)){
		ruby_imagecodec *codec;
		Data_Get_Struct( vcodec, ruby_imagecodec, codec);
		return codec->codec;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiImageCodec),rb_obj_classname(vcodec));
	}
}
#endif /* __RubyCeguiImageCodec_H__ */
