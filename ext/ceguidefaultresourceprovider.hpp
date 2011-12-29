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
	return unwrapPtr<CEGUI::DefaultResourceProvider>(vprovider, rb_cCeguiDefaultResourceProvider);
}
#endif /* __RubyCeguiDefaultResourceProvider_H__ */
