#ifndef __RubyCeguiKeyEventArgs_H__
#define __RubyCeguiKeyEventArgs_H__

#include "main.hpp"
void Init_CeguiKeyEventArgs(VALUE rb_mCegui);
extern VALUE rb_cCeguiKeyEventArgs;

template <>
inline VALUE wrap< CEGUI::KeyEventArgs >(CEGUI::KeyEventArgs *args )
{
	if(args==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiKeyEventArgs, NULL, NULL, args);
}

template <>
inline CEGUI::KeyEventArgs* wrap< CEGUI::KeyEventArgs* >(const VALUE &vargs)
{
	return unwrapPtr<CEGUI::KeyEventArgs>(vargs, rb_cCeguiKeyEventArgs);
}
#endif /* __RubyCeguiEventArgs_H__ */
