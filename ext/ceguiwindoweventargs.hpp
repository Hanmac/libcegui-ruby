#ifndef __RubyCeguiWindowEventArgs_H__
#define __RubyCeguiWindowEventArgs_H__

#include "main.hpp"
void Init_CeguiWindowEventArgs(VALUE rb_mCegui);
extern VALUE rb_cCeguiWindowEventArgs;

#include "ceguikeyeventargs.hpp"

template <>
inline VALUE wrap< CEGUI::WindowEventArgs >(CEGUI::WindowEventArgs *args )
{
	if(args==NULL)
		return Qnil;

	CEGUI::KeyEventArgs *kea = dynamic_cast<CEGUI::KeyEventArgs*>(args);
	if(kea)
		return wrap(kea);

	return Data_Wrap_Struct(rb_cCeguiWindowEventArgs, NULL, NULL, args);
}

template <>
inline CEGUI::WindowEventArgs* wrap< CEGUI::WindowEventArgs* >(const VALUE &vargs)
{
	return unwrapPtr<CEGUI::WindowEventArgs>(vargs, rb_cCeguiWindowEventArgs);
}
#endif /* __RubyCeguiEventArgs_H__ */
