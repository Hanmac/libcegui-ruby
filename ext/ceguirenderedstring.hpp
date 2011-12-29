#ifndef __RubyCeguiRenderedString_H__
#define __RubyCeguiRenderedString_H__

#include "main.hpp"
void Init_CeguiRenderedString(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderedString;


template <>
inline VALUE wrap< CEGUI::RenderedString >(CEGUI::RenderedString *renderedstring )
{
	if(renderedstring==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiRenderedString, NULL, NULL, renderedstring);
}

template <>
inline CEGUI::RenderedString* wrap< CEGUI::RenderedString* >(const VALUE &vrenderedstring)
{
	return unwrapPtr<CEGUI::RenderedString>(vrenderedstring, rb_cCeguiRenderedString);
}
#endif /* __RubyCeguiTree_H__ */
