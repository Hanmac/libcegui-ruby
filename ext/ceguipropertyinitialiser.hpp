/*
 * ceguipropertyinitialiser.hpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiPropertyInitialiser_H__
#define __RubyCeguiPropertyInitialiser_H__

#include "main.hpp"
void Init_CeguiPropertyInitialiser(VALUE rb_mCegui);
extern VALUE rb_cCeguiPropertyInitialiser;

template <>
inline VALUE wrap< CEGUI::PropertyInitialiser >(CEGUI::PropertyInitialiser *look )
{
	if(look==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiPropertyInitialiser, NULL, NULL, look);
}
template <>
inline CEGUI::PropertyInitialiser* wrap< CEGUI::PropertyInitialiser* >(const VALUE &vlook)
{
	return unwrapPtr<CEGUI::PropertyInitialiser>(vlook, rb_cCeguiPropertyInitialiser);
}
#endif /* __RubyCeguiPropertyInitialiser_H__ */
