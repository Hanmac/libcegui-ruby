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
	return unwrapPtr<CEGUI::Property>(vproperty, rb_cCeguiProperty);
}
#endif /* __RubyCeguiProperty_H__ */
