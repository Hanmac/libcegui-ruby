#ifndef __RubyCeguiUDim_H__
#define __RubyCeguiUDim_H__

#include "main.hpp"
void Init_CeguiUDim(VALUE rb_mCegui);
extern VALUE rb_cCeguiUDim;

#include "ceguiexception.hpp"

template <>
inline VALUE wrap< CEGUI::UDim >(CEGUI::UDim *dim )
{
	return Data_Wrap_Struct(rb_cCeguiUDim, NULL, free, dim);
}

template <>
inline bool is_wrapable< CEGUI::UDim >(const VALUE &vdim)
{
	if (rb_obj_is_kind_of(vdim, rb_cCeguiUDim)){
		return true;
	}else if(rb_respond_to(vdim,rb_intern("scale")) &&
		rb_respond_to(vdim,rb_intern("offset"))){
		return true;
	}else
		return false;
}

template <>
inline CEGUI::UDim* wrap< CEGUI::UDim* >(const VALUE &vdim)
{
	if (rb_obj_is_kind_of(vdim, rb_cCeguiUDim)){
		CEGUI::UDim *dim;
		Data_Get_Struct( vdim, CEGUI::UDim, dim);
		return dim;
	}else if(rb_respond_to(vdim,rb_intern("scale")) && 
	 rb_respond_to(vdim,rb_intern("offset"))){
	 	CEGUI::UDim *dim = new CEGUI::UDim;
	 	dim->d_scale = NUM2DBL(rb_funcall(vdim,rb_intern("scale"),0));
	 	dim->d_offset = NUM2DBL(rb_funcall(vdim,rb_intern("offset"),0));
	 	return dim;
	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiUDim),rb_obj_classname(vdim));
		return NULL;
	}

}
template <>
inline CEGUI::UDim wrap< CEGUI::UDim >(const VALUE &vdim)
{
	return *wrap< CEGUI::UDim* >(vdim);
}
#endif /* __RubyCeguiUDim_H__ */
