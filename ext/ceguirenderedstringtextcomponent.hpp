#ifndef __RubyCeguiRenderedStringTextComponent_H__
#define __RubyCeguiRenderedStringTextComponent_H__

#include "main.hpp"
void Init_CeguiRenderedStringTextComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderedStringTextComponent;


template <>
inline VALUE wrap< CEGUI::RenderedStringTextComponent >(CEGUI::RenderedStringTextComponent *component )
{
	if(component==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiRenderedStringTextComponent, NULL, NULL, component);
}

template <>
inline CEGUI::RenderedStringTextComponent* wrap< CEGUI::RenderedStringTextComponent* >(const VALUE &vcomponent)
{
	if (rb_obj_is_kind_of(vcomponent, rb_cCeguiRenderedStringTextComponent)){
		CEGUI::RenderedStringTextComponent *component;
		Data_Get_Struct( vcomponent, CEGUI::RenderedStringTextComponent, component);
		return component;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",
			rb_class2name(rb_cCeguiRenderedStringTextComponent),rb_obj_classname(vcomponent));
		return NULL;
	}
}
#endif /* __RubyCeguiRenderedStringTextComponent_H__ */
