#ifndef __RubyCeguiUVector2_H__
#define __RubyCeguiUVector2_H__

#include "main.hpp"
void Init_CeguiUVector2(VALUE rb_mCegui);
extern VALUE rb_cCeguiUVector2;

#include "ceguiudim.hpp"

template <>
inline VALUE wrap< CEGUI::UVector2 >(CEGUI::UVector2 *vector )
{
	return Data_Wrap_Struct(rb_cCeguiUVector2, NULL, free, vector);
}

template <>
inline bool is_wrapable< CEGUI::UVector2 >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cCeguiUVector2)){
		return true;
	}else if(rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("y"))){
		return is_wrapable<CEGUI::UDim>(rb_funcall(vvector,rb_intern("x"),0))
			&& is_wrapable<CEGUI::UDim>(rb_funcall(vvector,rb_intern("y"),0));
	}else
		return false;
}

template <>
inline CEGUI::UVector2* wrap< CEGUI::UVector2* >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cCeguiUVector2)){
		CEGUI::UVector2 *vector;
		Data_Get_Struct( vvector, CEGUI::UVector2, vector);
		return vector;
	}else if(rb_respond_to(vvector,rb_intern("x")) && 
	 rb_respond_to(vvector,rb_intern("y"))){
	 	CEGUI::UVector2 *vector = new CEGUI::UVector2;
	 	vector->d_x = wrap<CEGUI::UDim>(rb_funcall(vvector,rb_intern("x"),0));
	 	vector->d_y = wrap<CEGUI::UDim>(rb_funcall(vvector,rb_intern("y"),0));
	 	return vector;
	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiUVector2),rb_obj_classname(vvector));
		return NULL;
	}

}
template <>
inline CEGUI::UVector2 wrap< CEGUI::UVector2 >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cString))
		return CEGUI::PropertyHelper<CEGUI::UVector2>::fromString(wrap<CEGUI::String>(vvector));
	else
		return *wrap< CEGUI::UVector2* >(vvector);
}
#endif /* __RubyCeguiUVector2_H__ */
