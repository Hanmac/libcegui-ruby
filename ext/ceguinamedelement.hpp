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
	if (rb_obj_is_kind_of(velement, rb_cCeguiNamedElement)){
		CEGUI::NamedElement *element;
		Data_Get_Struct( velement, CEGUI::NamedElement, element);
		return element;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiNamedElement),rb_obj_classname(velement));
		return NULL;
	}
}
#endif /* __RubyCeguiNamedElement_H__ */
