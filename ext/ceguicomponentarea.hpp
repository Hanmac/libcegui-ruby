/*
 * ceguicomponentarea.hpp
 *
 *  Created on: 09.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiComponentArea_H__
#define __RubyCeguiComponentArea_H__

#include "main.hpp"
void Init_CeguiComponentArea(VALUE rb_mCegui);
extern VALUE rb_cCeguiComponentArea;


template <>
inline VALUE wrap< CEGUI::ComponentArea >(CEGUI::ComponentArea *component )
{
	return Data_Wrap_Struct(rb_cCeguiComponentArea, NULL, NULL, component);
}

template <>
inline CEGUI::ComponentArea* wrap< CEGUI::ComponentArea* >(const VALUE &vcomponent)
{
	if (rb_obj_is_kind_of(vcomponent, rb_cCeguiComponentArea)){
		CEGUI::ComponentArea *component;
		Data_Get_Struct( vcomponent, CEGUI::ComponentArea, component);
		return component;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiComponentArea),rb_obj_classname(vcomponent));
		return NULL;
	}
}
#endif /* __RubyCeguiComponentArea_H__ */
