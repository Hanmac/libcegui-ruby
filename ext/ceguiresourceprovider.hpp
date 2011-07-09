#ifndef __RubyCeguiResourceProvider_H__
#define __RubyCeguiResourceProvider_H__

#include "main.hpp"
void Init_CeguiResourceProvider(VALUE rb_mCegui);
extern VALUE rb_cCeguiResourceProvider;

#include "ceguidefaultresourceprovider.hpp"
template <>
inline VALUE wrap< CEGUI::ResourceProvider >(CEGUI::ResourceProvider *provider )
{
	if(provider==NULL)
		return Qnil;
	CEGUI::DefaultResourceProvider *defaultprovider = dynamic_cast<CEGUI::DefaultResourceProvider*>(provider);
	if(defaultprovider)
		return wrap(defaultprovider);

	return Data_Wrap_Struct(rb_cCeguiResourceProvider, NULL, NULL, provider);
}
template <>
inline CEGUI::ResourceProvider* wrap< CEGUI::ResourceProvider* >(const VALUE &vprovider)
{
	if (rb_obj_is_kind_of(vprovider, rb_cCeguiResourceProvider)){
		CEGUI::ResourceProvider *provider;
		Data_Get_Struct( vprovider, CEGUI::ResourceProvider, provider);
		return provider;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiResourceProvider),rb_obj_classname(vprovider));
		return NULL;
	}
}
#endif /* __RubyCeguiResourceProvider_H__ */
