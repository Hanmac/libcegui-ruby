/*
 * ceguisectionspecification.hpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiSectionSpecification_H__
#define __RubyCeguiSectionSpecification_H__

#include "main.hpp"
void Init_CeguiSectionSpecification(VALUE rb_mCegui);
extern VALUE rb_cCeguiSectionSpecification;

template <>
inline VALUE wrap< CEGUI::SectionSpecification >(CEGUI::SectionSpecification *section )
{
	if(section==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiSectionSpecification, NULL, NULL, section);
}
template <>
inline CEGUI::SectionSpecification* wrap< CEGUI::SectionSpecification* >(const VALUE &vsection)
{
	return unwrapPtr<CEGUI::SectionSpecification>(vsection, rb_cCeguiSectionSpecification);
}
#endif /* __RubyCeguiSectionSpecification_H__ */
