#ifndef __RubyCeguiVector2_H__
#define __RubyCeguiVector2_H__

#include "main.hpp"
void Init_CeguiVector2(VALUE rb_mCegui);
extern VALUE rb_cCeguiVector2;


template <>
inline VALUE wrap< CEGUI::Vector2f >(CEGUI::Vector2f *vector )
{
	return Data_Wrap_Struct(rb_cCeguiVector2, NULL, free, vector);
}

template <>
inline bool is_wrapable< CEGUI::Vector2f >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cCeguiVector2)){
		return true;
	}else if(rb_respond_to(vvector,rb_intern("x")) &&
		rb_respond_to(vvector,rb_intern("y"))){
		return true;
	}else
		return false;
}

template <>
inline CEGUI::Vector2f* wrap< CEGUI::Vector2f* >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cCeguiVector2)){
		CEGUI::Vector2f *vector;
		Data_Get_Struct( vvector, CEGUI::Vector2f, vector);
		return vector;
	}else if(rb_respond_to(vvector,rb_intern("x")) && 
	 rb_respond_to(vvector,rb_intern("y"))){
	 	CEGUI::Vector2f *vector = new CEGUI::Vector2f;
	 	vector->d_x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
	 	vector->d_y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
	 	return vector;
	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiVector2),rb_obj_classname(vvector));
		return NULL;
	}

}
template <>
inline CEGUI::Vector2f wrap< CEGUI::Vector2f >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cString))
		return CEGUI::PropertyHelper<CEGUI::Vector2f>::fromString(wrap<CEGUI::String>(vvector));
	else
		return *wrap< CEGUI::Vector2f* >(vvector);
}
#endif /* __RubyCeguiVector2_H__ */
