#ifndef __RubyCeguiNamedElement_H__
#define __RubyCeguiNamedElement_H__

#include "main.hpp"
void Init_CeguiNamedElement(VALUE rb_mCegui);

extern VALUE rb_cCeguiNamedElement;

#include "ceguiwindow.hpp"

template <>
inline VALUE wrap< CEGUI::NamedElement >(CEGUI::NamedElement *element )
{
	if(element==NULL)
		return Qnil;
	
	CEGUI::Window *window = dynamic_cast<CEGUI::Window*>(element);
	if(window)
		return wrap(window);
	
	return Data_Wrap_Struct(rb_cCeguiNamedElement, NULL, free, element);
}


template <>
inline CEGUI::NamedElement* wrap< CEGUI::NamedElement* >(const VALUE &velement)
{
	if (rb_obj_is_kind_of(velement, rb_cCeguiWindow)){
		return wrap<CEGUI::Window*>(velement);
	}
	return unwrapPtr<CEGUI::NamedElement>(velement, rb_cCeguiNamedElement);
}
#endif /* __RubyCeguiNamedElement_H__ */
