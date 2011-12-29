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
	return unwrapPtr<CEGUI::ComponentArea>(vcomponent, rb_cCeguiComponentArea);
}
#endif /* __RubyCeguiComponentArea_H__ */
