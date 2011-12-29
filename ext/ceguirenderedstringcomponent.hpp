#ifndef __RubyCeguiRenderedStringComponent_H__
#define __RubyCeguiRenderedStringComponent_H__

#include "main.hpp"
void Init_CeguiRenderedStringComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderedStringComponent;

#include "ceguiexception.hpp"
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
	return unwrapPtr<CEGUI::RenderedStringComponent>(vcomponent, rb_cCeguiRenderedStringComponent);
}
#endif /* __RubyCeguiRenderedStringComponent_H__ */
