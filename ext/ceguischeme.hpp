#ifndef __RubyCeguiScheme_H__
#define __RubyCeguiScheme_H__

#include "main.hpp"
#include "ceguiexception.hpp"
void Init_CeguiScheme(VALUE rb_mCegui);
extern VALUE rb_cCeguiScheme;

template <>
inline VALUE wrap< CEGUI::Scheme >(CEGUI::Scheme *scheme )
{
	if(scheme==NULL)
		return Qnil;
		RubyResource *temp = new RubyResource;
	temp->name = scheme->getName();
	return Data_Wrap_Struct(rb_cCeguiScheme, NULL, NULL, temp);
}
template <>
inline CEGUI::Scheme* wrap< CEGUI::Scheme* >(const VALUE &vscheme)
{
	try {
		if (rb_obj_is_kind_of(vscheme, rb_cString)){
			return &CEGUI::SchemeManager::getSingletonPtr()->get(wrap<CEGUI::String>(vscheme));
		}else	if (rb_obj_is_kind_of(vscheme, rb_cCeguiScheme)){
			RubyResource *scheme;
			Data_Get_Struct( vscheme, RubyResource, scheme);
			return &CEGUI::SchemeManager::getSingletonPtr()->get(scheme->name);
		}else{
			rb_raise(rb_eTypeError,"Excepted %s got %s!",
				rb_class2name(rb_cCeguiScheme),rb_obj_classname(vscheme));
			return NULL;
		}
	}catch(CEGUI::Exception& e){
		rb_raise(e);
		return NULL;
	}
}
#endif /* __RubyCeguiScheme_H__ */
