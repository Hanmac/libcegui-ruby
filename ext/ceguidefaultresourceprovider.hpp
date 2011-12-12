#ifndef __RubyCeguiDefaultResourceProvider_H__
#define __RubyCeguiDefaultResourceProvider_H__

#include "main.hpp"
void Init_CeguiDefaultResourceProvider(VALUE rb_mCegui);
extern VALUE rb_cCeguiDefaultResourceProvider;

template <>
inline VALUE wrap< CEGUI::DefaultResourceProvider >(CEGUI::DefaultResourceProvider *provider )
{
	if(provider==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiDefaultResourceProvider, NULL, NULL, provider);
}
template <>
inline CEGUI::DefaultResourceProvider* wrap< CEGUI::DefaultResourceProvider* >(const VALUE &vprovider)
{
	if (rb_obj_is_kind_of(vprovider, rb_cCeguiDefaultResourceProvider)){
		CEGUI::DefaultResourceProvider *provider;
		Data_Get_Struct( vprovider, CEGUI::DefaultResourceProvider, provider);
		return provider;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiDefaultResourceProvider),rb_obj_classname(vprovider));
		return NULL;
	}
}
#endif /* __RubyCeguiDefaultResourceProvider_H__ */
