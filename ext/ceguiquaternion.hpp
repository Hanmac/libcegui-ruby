/*
 * quaternion.hpp
 *
 *  Created on: 01.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiQuaternion_H__
#define __RubyCeguiQuaternion_H__

#include "main.hpp"
void Init_CeguiQuaternion(VALUE rb_mCegui);
extern VALUE rb_cCeguiQuaternion;


template <>
inline VALUE wrap< CEGUI::Quaternion >(CEGUI::Quaternion *quaternion )
{
	return Data_Wrap_Struct(rb_cCeguiQuaternion, NULL, free, quaternion);
}

template <>
inline bool is_wrapable< CEGUI::Quaternion >(const VALUE &vquaternion)
{
	if(rb_obj_is_kind_of(vquaternion, rb_cCeguiQuaternion)){
		return true;
	}else if(rb_respond_to(vquaternion,rb_intern("w")) &&
		rb_respond_to(vquaternion,rb_intern("x")) &&
		rb_respond_to(vquaternion,rb_intern("y")) &&
		rb_respond_to(vquaternion,rb_intern("z"))){
		return true;
	}else
		return false;
}

template <>
inline CEGUI::Quaternion* wrap< CEGUI::Quaternion* >(const VALUE &vquaternion)
{
	if (rb_obj_is_kind_of(vquaternion, rb_cCeguiQuaternion)){
		CEGUI::Quaternion *quaternion;
		Data_Get_Struct( vquaternion, CEGUI::Quaternion, quaternion);
		return quaternion;
	}else if(rb_respond_to(vquaternion,rb_intern("w")) &&
	 rb_respond_to(vquaternion,rb_intern("x")) &&
	 rb_respond_to(vquaternion,rb_intern("y")) &&
	 rb_respond_to(vquaternion,rb_intern("z"))){
	 	CEGUI::Quaternion *quaternion = new CEGUI::Quaternion;
	 	quaternion->d_w = NUM2DBL(rb_funcall(vquaternion,rb_intern("w"),0));
	 	quaternion->d_x = NUM2DBL(rb_funcall(vquaternion,rb_intern("x"),0));
	 	quaternion->d_y = NUM2DBL(rb_funcall(vquaternion,rb_intern("y"),0));
	 	quaternion->d_z = NUM2DBL(rb_funcall(vquaternion,rb_intern("z"),0));
	 	return quaternion;
	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiQuaternion),rb_obj_classname(vquaternion));
		return NULL;
	}
}
template <>
inline CEGUI::Quaternion wrap< CEGUI::Quaternion >(const VALUE &vquaternion)
{
	if (rb_obj_is_kind_of(vquaternion, rb_cString))
		return CEGUI::PropertyHelper<CEGUI::Quaternion>::fromString(wrap<CEGUI::String>(vquaternion));
	else
		return *wrap< CEGUI::Quaternion* >(vquaternion);
}
#endif /* __RubyCeguiQuaternion_H__ */

