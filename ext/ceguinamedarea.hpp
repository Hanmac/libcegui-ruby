/*
 * ceguinamedarea.hpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiNamedArea_H__
#define __RubyCeguiNamedArea_H__

#include "main.hpp"
void Init_CeguiNamedArea(VALUE rb_mCegui);
extern VALUE rb_cCeguiNamedArea;

template <>
inline VALUE wrap< CEGUI::NamedArea >(CEGUI::NamedArea *look )
{
	if(look==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiNamedArea, NULL, NULL, look);
}
template <>
inline CEGUI::NamedArea* wrap< CEGUI::NamedArea* >(const VALUE &vlook)
{
	return unwrapPtr<CEGUI::NamedArea>(vlook, rb_cCeguiNamedArea);
}
#endif /* __RubyCeguiNamedArea_H__ */
