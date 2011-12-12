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
	if (rb_obj_is_kind_of(vargs, rb_cCeguiKeyEventArgs)){
		CEGUI::KeyEventArgs *args;
		Data_Get_Struct( vargs, CEGUI::KeyEventArgs, args);
		return args;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiKeyEventArgs),rb_obj_classname(vargs));
		return NULL;
	}
}
#endif /* __RubyCeguiEventArgs_H__ */
