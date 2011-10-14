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
	if (rb_obj_is_kind_of(vrenderedstring, rb_cCeguiRenderedString)){
		CEGUI::RenderedString *renderedstring;
		Data_Get_Struct( vrenderedstring, CEGUI::RenderedString, renderedstring);
		return renderedstring;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",
			rb_class2name(rb_cCeguiRenderedString),rb_obj_classname(vrenderedstring));
		return NULL;
	}
}
#endif /* __RubyCeguiTree_H__ */
