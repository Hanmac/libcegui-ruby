#ifndef __RubyCeguiScheme_H__
#define __RubyCeguiScheme_H__

#include "main.hpp"
void Init_CeguiScheme(VALUE rb_mCegui);
extern VALUE rb_cCeguiScheme;

template <>
inline VALUE wrap< CEGUI::Scheme >(CEGUI::Scheme *scheme )
{
	if(scheme==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiScheme, NULL, NULL, scheme);
}
template <>
inline CEGUI::Scheme* wrap< CEGUI::Scheme* >(const VALUE &vscheme)
{
	if (rb_obj_is_kind_of(vscheme, rb_cString)){
		return &CEGUI::SchemeManager::getSingletonPtr()->get(wrap<CEGUI::String>(vscheme));
	}else	if (rb_obj_is_kind_of(vscheme, rb_cCeguiScheme)){
		CEGUI::Scheme *scheme;
		Data_Get_Struct( vscheme, CEGUI::Scheme, scheme);
		return scheme;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiScheme),rb_obj_classname(vscheme));
		return NULL;
	}
}
#endif /* __RubyCeguiScheme_H__ */
