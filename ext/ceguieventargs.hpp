#ifndef __RubyCeguiEventArgs_H__
#define __RubyCeguiEventArgs_H__

#include "main.hpp"
void Init_CeguiEventArgs(VALUE rb_mCegui);
extern VALUE rb_cCeguiEventArgs;

#include "ceguiwindoweventargs.hpp"

template <>
inline VALUE wrap< CEGUI::EventArgs >(CEGUI::EventArgs *args )
{
	if(args==NULL)
		return Qnil;
	CEGUI::KeyEventArgs *kea = dynamic_cast<CEGUI::KeyEventArgs*>(args);
	if(kea)
		return wrap(kea);

	CEGUI::WindowEventArgs *wea = dynamic_cast<CEGUI::WindowEventArgs*>(args);
	if(wea)
		return wrap(wea);

	return Data_Wrap_Struct(rb_cCeguiEventArgs, NULL, NULL, args);
}
template <>
inline VALUE wrap<const CEGUI::EventArgs >(const CEGUI::EventArgs *args )
{
	return wrap(const_cast<CEGUI::EventArgs*>(args));
}
template <>
inline CEGUI::EventArgs* wrap< CEGUI::EventArgs* >(const VALUE &vargs)
{
	return unwrapPtr<CEGUI::EventArgs>(vargs, rb_cCeguiEventArgs);
}
#endif /* __RubyCeguiEventArgs_H__ */
