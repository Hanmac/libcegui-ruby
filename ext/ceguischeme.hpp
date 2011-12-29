#ifndef __RubyCeguiScheme_H__
#define __RubyCeguiScheme_H__

#include "ceguiresource.hpp"

void Init_CeguiScheme(VALUE rb_mCegui);
extern VALUE rb_cCeguiScheme;

template <>
inline VALUE wrap< CEGUI::Scheme >(CEGUI::Scheme *scheme )
{
	if(scheme==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiScheme, NULL, NULL,
			new RubyResource(scheme->getName()));
}


template <>
inline CEGUI::Scheme* unwrapResource_impl<CEGUI::Scheme>(CEGUI::String name)
{
	return &CEGUI::SchemeManager::getSingletonPtr()->get(name);
}


template <>
inline CEGUI::Scheme* wrap< CEGUI::Scheme* >(const VALUE &vscheme)
{
	return unwrapResource<CEGUI::Scheme>(vscheme, rb_cCeguiScheme);
}
#endif /* __RubyCeguiScheme_H__ */
