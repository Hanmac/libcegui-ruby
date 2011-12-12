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
	if (rb_obj_is_kind_of(vargs, rb_cCeguiWindowEventArgs)){
		CEGUI::WindowEventArgs *args;
		Data_Get_Struct( vargs, CEGUI::WindowEventArgs, args);
		return args;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiWindowEventArgs),rb_obj_classname(vargs));
		return NULL;
	}
}
#endif /* __RubyCeguiEventArgs_H__ */
