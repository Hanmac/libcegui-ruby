#ifndef __RubyCeguiRenderedStringImageComponent_H__
#define __RubyCeguiRenderedStringImageComponent_H__

#include "main.hpp"
void Init_CeguiRenderedStringImageComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderedStringImageComponent;


template <>
inline VALUE wrap< CEGUI::RenderedStringImageComponent >(CEGUI::RenderedStringImageComponent *component )
{
	if(component==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiRenderedStringImageComponent, NULL, NULL, component);
}

template <>
inline CEGUI::RenderedStringImageComponent* wrap< CEGUI::RenderedStringImageComponent* >(const VALUE &vcomponent)
{
	if (rb_obj_is_kind_of(vcomponent, rb_cCeguiRenderedStringImageComponent)){
		CEGUI::RenderedStringImageComponent *component;
		Data_Get_Struct( vcomponent, CEGUI::RenderedStringImageComponent, component);
		return component;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",
			rb_class2name(rb_cCeguiRenderedStringImageComponent),rb_obj_classname(vcomponent));
		return NULL;
	}
}
#endif /* __RubyCeguiRenderedStringImageComponent_H__ */
