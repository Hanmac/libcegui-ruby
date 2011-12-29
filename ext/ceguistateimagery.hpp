/*
 * ceguistateimagery.hpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiStateImagery_H__
#define __RubyCeguiStateImagery_H__

#include "main.hpp"
void Init_CeguiStateImagery(VALUE rb_mCegui);
extern VALUE rb_cCeguiStateImagery;

template <>
inline VALUE wrap< CEGUI::StateImagery >(CEGUI::StateImagery *section )
{
	if(section==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiStateImagery, NULL, NULL, section);
}
template <>
inline CEGUI::StateImagery* wrap< CEGUI::StateImagery* >(const VALUE &vsection)
{
	return unwrapPtr<CEGUI::StateImagery>(vsection, rb_cCeguiStateImagery);
}
#endif /* __RubyCeguiStateImagery_H__ */
