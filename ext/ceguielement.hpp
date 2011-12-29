#ifndef __RubyCeguiElement_H__
#define __RubyCeguiElement_H__

#include "main.hpp"
void Init_CeguiElement(VALUE rb_mCegui);

extern VALUE rb_cCeguiElement;

#include "ceguinamedelement.hpp"
#include "ceguiexception.hpp"
template <>
inline VALUE wrap< CEGUI::Element >(CEGUI::Element *element )
{
	if(element==NULL)
		return Qnil;
	
	CEGUI::NamedElement *namedelement = dynamic_cast<CEGUI::NamedElement*>(element);
	if(namedelement)
		return wrap(namedelement);
	
	return Data_Wrap_Struct(rb_cCeguiElement, NULL, free, element);
}


template <>
inline CEGUI::Element* wrap< CEGUI::Element* >(const VALUE &velement)
{
	if (rb_obj_is_kind_of(velement, rb_cCeguiNamedElement)){
		return wrap<CEGUI::NamedElement*>(velement);
	}else
	return unwrapPtr<CEGUI::Element>(velement, rb_cCeguiElement);
}


template <>
inline VALUE wrap< CEGUI::HorizontalAlignment >(const CEGUI::HorizontalAlignment &alignment )
{
	return ID2SYM(rb_intern(CEGUI::PropertyHelper<CEGUI::HorizontalAlignment>::toString(alignment).c_str()));
}

template <>
inline CEGUI::HorizontalAlignment wrap< CEGUI::HorizontalAlignment >(const VALUE &alignment)
{
	VALUE result = rb_funcall(alignment,rb_intern("to_sym"),0);
	return CEGUI::PropertyHelper<CEGUI::HorizontalAlignment>::fromString(rb_id2name(SYM2ID(result)));
}

template <>
inline VALUE wrap< CEGUI::VerticalAlignment >(const CEGUI::VerticalAlignment &alignment )
{
	return ID2SYM(rb_intern(CEGUI::PropertyHelper<CEGUI::VerticalAlignment>::toString(alignment).c_str()));
}

template <>
inline CEGUI::VerticalAlignment wrap< CEGUI::VerticalAlignment >(const VALUE &alignment)
{
	VALUE result = rb_funcall(alignment,rb_intern("to_sym"),0);
	return CEGUI::PropertyHelper<CEGUI::VerticalAlignment>::fromString(rb_id2name(SYM2ID(result)));
}

#endif /* __RubyCeguiElement_H__ */
