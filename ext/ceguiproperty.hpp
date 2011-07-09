#ifndef __RubyCeguiProperty_H__
#define __RubyCeguiProperty_H__

#include "main.hpp"
void Init_CeguiProperty(VALUE rb_mCegui);
extern VALUE rb_cCeguiProperty;


template <>
inline VALUE wrap< CEGUI::Property >(CEGUI::Property *property )
{
	if(property==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiProperty, NULL, NULL, property);
}

template <>
inline CEGUI::Property* wrap< CEGUI::Property* >(const VALUE &vproperty)
{
	if (rb_obj_is_kind_of(vproperty, rb_cCeguiProperty)){
		CEGUI::Property *property;
		Data_Get_Struct( vproperty, CEGUI::Property, property);
		return property;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiProperty),rb_obj_classname(vproperty));
		return NULL;
	}
}
#endif /* __RubyCeguiProperty_H__ */
