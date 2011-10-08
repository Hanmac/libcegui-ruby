#ifndef __RubyCeguiVector3_H__
#define __RubyCeguiVector3_H__

#include "main.hpp"
void Init_CeguiVector3(VALUE rb_mCegui);
extern VALUE rb_cCeguiVector3;


template <>
inline VALUE wrap< CEGUI::Vector3f >(CEGUI::Vector3f *vector )
{
	return Data_Wrap_Struct(rb_cCeguiVector3, NULL, free, vector);
}

template <>
inline CEGUI::Vector3f* wrap< CEGUI::Vector3f* >(const VALUE &vvector)
{
	if (rb_obj_is_kind_of(vvector, rb_cCeguiVector3)){
		CEGUI::Vector3f *vector;
		Data_Get_Struct( vvector, CEGUI::Vector3f, vector);
		return vector;
	}else if(rb_respond_to(vvector,rb_intern("x")) && 
	 rb_respond_to(vvector,rb_intern("y")) &&
	 rb_respond_to(vvector,rb_intern("z"))){
	 	CEGUI::Vector3f *vector = new CEGUI::Vector3f;
	 	vector->d_x = NUM2DBL(rb_funcall(vvector,rb_intern("x"),0));
	 	vector->d_y = NUM2DBL(rb_funcall(vvector,rb_intern("y"),0));
	 	vector->d_z = NUM2DBL(rb_funcall(vvector,rb_intern("z"),0));
	 	return vector;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiVector3),rb_obj_classname(vvector));
		return NULL;
	}
}
template <>
inline CEGUI::Vector3f wrap< CEGUI::Vector3f >(const VALUE &vvector)
{
	return *wrap< CEGUI::Vector3f* >(vvector);
}
#endif /* __RubyCeguiVector3_H__ */
