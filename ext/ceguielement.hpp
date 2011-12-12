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
	}else if (rb_obj_is_kind_of(velement, rb_cCeguiElement)){
		CEGUI::Element *element;
		Data_Get_Struct( velement, CEGUI::Element, element);
		return element;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiElement),rb_obj_classname(velement));
		return NULL;
	}
}


template <>
inline VALUE wrap< CEGUI::HorizontalAlignment >(const CEGUI::HorizontalAlignment &alignment )
{
	switch(alignment){
	case CEGUI::HA_CENTRE:
		return ID2SYM(rb_intern("Centre"));
	case CEGUI::HA_RIGHT:
		return ID2SYM(rb_intern("Right"));
	case CEGUI::HA_LEFT:
		return ID2SYM(rb_intern("Left"));
	default:
		return ID2SYM(rb_intern("Left"));
	}
}

template <>
inline CEGUI::HorizontalAlignment wrap< CEGUI::HorizontalAlignment >(const VALUE &alignment)
{
	ID result = SYM2ID(alignment);
	if(result == rb_intern("Centre")){
		return CEGUI::HA_CENTRE;
	}if(result == rb_intern("Right"))
		return CEGUI::HA_RIGHT;
	if(result == rb_intern("Left"))
		return CEGUI::HA_LEFT;
	return CEGUI::HA_CENTRE;
}

template <>
inline VALUE wrap< CEGUI::VerticalAlignment >(const CEGUI::VerticalAlignment &alignment )
{
	switch(alignment){
	case CEGUI::VA_CENTRE:
		return ID2SYM(rb_intern("Centre"));
	case CEGUI::VA_BOTTOM:
		return ID2SYM(rb_intern("Bottom"));
	case CEGUI::VA_TOP:
		return ID2SYM(rb_intern("Top"));
	default:
		return ID2SYM(rb_intern("Top"));
	}
}

template <>
inline CEGUI::VerticalAlignment wrap< CEGUI::VerticalAlignment >(const VALUE &alignment)
{
	ID result = SYM2ID(alignment);
	if(result == rb_intern("Centre")){
		return CEGUI::VA_CENTRE;
	}if(result == rb_intern("Bottom"))
		return CEGUI::VA_BOTTOM;
	if(result == rb_intern("Top"))
		return CEGUI::VA_TOP;
	return CEGUI::VA_CENTRE;
}

#endif /* __RubyCeguiElement_H__ */
