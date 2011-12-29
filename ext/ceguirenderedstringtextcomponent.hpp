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
	return unwrapPtr<CEGUI::RenderedStringTextComponent>(vcomponent, rb_cCeguiRenderedStringTextComponent);
}
#endif /* __RubyCeguiRenderedStringTextComponent_H__ */
