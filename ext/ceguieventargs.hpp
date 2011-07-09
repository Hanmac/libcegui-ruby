#ifndef __RubyCeguiEventArgs_H__
#define __RubyCeguiEventArgs_H__

#include "main.hpp"
void Init_CeguiEventArgs(VALUE rb_mCegui);
extern VALUE rb_cCeguiEventArgs;


template <>
inline VALUE wrap< CEGUI::EventArgs >(CEGUI::EventArgs *args )
{
	if(args==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiEventArgs, NULL, NULL, args);
}

template <>
inline CEGUI::EventArgs* wrap< CEGUI::EventArgs* >(const VALUE &vargs)
{
	if (rb_obj_is_kind_of(vargs, rb_cCeguiEventArgs)){
		CEGUI::EventArgs *args;
		Data_Get_Struct( vargs, CEGUI::EventArgs, args);
		return args;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiEventArgs),rb_obj_classname(vargs));
		return NULL;
	}
}
#endif /* __RubyCeguiEventArgs_H__ */
