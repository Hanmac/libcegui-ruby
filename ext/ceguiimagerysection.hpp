/*
 * ceguiimagerysection.hpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiImagerySection_H__
#define __RubyCeguiImagerySection_H__

#include "main.hpp"
void Init_CeguiImagerySection(VALUE rb_mCegui);
extern VALUE rb_cCeguiImagerySection;

template <>
inline VALUE wrap< CEGUI::ImagerySection >(CEGUI::ImagerySection *section )
{
	if(section==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiImagerySection, NULL, NULL, section);
}
template <>
inline CEGUI::ImagerySection* wrap< CEGUI::ImagerySection* >(const VALUE &vsection)
{
	return unwrapPtr<CEGUI::ImagerySection>(vsection, rb_cCeguiImagerySection);
}
#endif /* __RubyCeguiImagerySection_H__ */
