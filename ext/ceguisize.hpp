#ifndef __RubyCeguiSize_H__
#define __RubyCeguiSize_H__

#include "main.hpp"
void Init_CeguiSize(VALUE rb_mCegui);
extern VALUE rb_cCeguiSize;


template <>
inline VALUE wrap< CEGUI::Sizef >(CEGUI::Sizef *size )
{
	return Data_Wrap_Struct(rb_cCeguiSize, NULL, free, size);
}

template <>
inline CEGUI::Sizef* wrap< CEGUI::Sizef* >(const VALUE &vsize)
{
	if (rb_obj_is_kind_of(vsize, rb_cCeguiSize)){
		CEGUI::Sizef *size;
		Data_Get_Struct( vsize, CEGUI::Sizef, size);
		return size;
	}else if(rb_respond_to(vsize,rb_intern("width")) && 
	 rb_respond_to(vsize,rb_intern("height"))){
	 	CEGUI::Sizef *size = new CEGUI::Sizef;
	 	size->d_width = NUM2DBL(rb_funcall(vsize,rb_intern("width"),0));
	 	size->d_height = NUM2DBL(rb_funcall(vsize,rb_intern("height"),0));
	 	return size;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiSize),rb_obj_classname(vsize));
		return NULL;
	}

}
template <>
inline CEGUI::Sizef wrap< CEGUI::Sizef >(const VALUE &vsize)
{
	return *wrap< CEGUI::Sizef* >(vsize);
}
#endif /* __RubyCeguiSize_H__ */
