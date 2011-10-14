#ifndef __RubyCeguiRenderedStringComponent_H__
#define __RubyCeguiRenderedStringComponent_H__

#include "main.hpp"
void Init_CeguiRenderedStringComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderedStringComponent;

#include "ceguirenderedstringtextcomponent.hpp"
#include "ceguirenderedstringimagecomponent.hpp"

template <>
inline VALUE wrap< CEGUI::RenderedStringComponent >(CEGUI::RenderedStringComponent *component )
{
	if(component==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiRenderedStringComponent, NULL, NULL, component);
}

template <>
inline CEGUI::RenderedStringComponent* wrap< CEGUI::RenderedStringComponent* >(const VALUE &vcomponent)
{
	if (rb_obj_is_kind_of(vcomponent, rb_cCeguiRenderedStringComponent)){
		CEGUI::RenderedStringComponent *component;
		Data_Get_Struct( vcomponent, CEGUI::RenderedStringComponent, component);
		return component;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",
			rb_class2name(rb_cCeguiRenderedStringComponent),rb_obj_classname(vcomponent));
		return NULL;
	}
}
#endif /* __RubyCeguiRenderedStringComponent_H__ */
