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
	return unwrapPtr<CEGUI::RenderedStringImageComponent>(vcomponent, rb_cCeguiRenderedStringImageComponent);
}
#endif /* __RubyCeguiRenderedStringImageComponent_H__ */
