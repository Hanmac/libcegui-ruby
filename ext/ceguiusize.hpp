/*
 * ceguiusize.hpp
 *
 *  Created on: 06.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiUSize_H__
#define __RubyCeguiUSize_H__

#include "ceguiudim.hpp"
void Init_CeguiUSize(VALUE rb_mCegui);
extern VALUE rb_cCeguiUSize;


template <>
inline VALUE wrap< CEGUI::USize >(CEGUI::USize *size )
{
	return Data_Wrap_Struct(rb_cCeguiUSize, NULL, free, size);
}


template <>
inline bool is_wrapable< CEGUI::USize >(const VALUE &vsize)
{
	if (rb_obj_is_kind_of(vsize, rb_cCeguiUSize)){
		return true;
	}else if(rb_respond_to(vsize,rb_intern("width")) &&
		rb_respond_to(vsize,rb_intern("height"))){
		return true;
	}else
		return false;
}

template <>
inline CEGUI::USize* wrap< CEGUI::USize* >(const VALUE &vsize)
{
	if (rb_obj_is_kind_of(vsize, rb_cCeguiUSize)){
		CEGUI::USize *size;
		Data_Get_Struct( vsize, CEGUI::USize, size);
		return size;
	}else if(rb_respond_to(vsize,rb_intern("width")) &&
	 rb_respond_to(vsize,rb_intern("height"))){
	 	CEGUI::USize *size = new CEGUI::USize;
	 	size->d_width = wrap<CEGUI::UDim>(rb_funcall(vsize,rb_intern("width"),0));
	 	size->d_height = wrap<CEGUI::UDim>(rb_funcall(vsize,rb_intern("height"),0));
	 	return size;
	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiUSize),rb_obj_classname(vsize));
		return NULL;
	}

}
template <>
inline CEGUI::USize wrap< CEGUI::USize >(const VALUE &vsize)
{
	if (rb_obj_is_kind_of(vsize, rb_cString))
		return CEGUI::PropertyHelper<CEGUI::USize>::fromString(wrap<CEGUI::String>(vsize));
	else
		return *wrap< CEGUI::USize* >(vsize);
}
#endif /* __RubyCeguiSize_H__ */
