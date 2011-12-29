/*
 * ceguilayerspecification.hpp
 *
 *  Created on: 23.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiLayerSpecification_H__
#define __RubyCeguiLayerSpecification_H__

#include "main.hpp"
void Init_CeguiLayerSpecification(VALUE rb_mCegui);
extern VALUE rb_cCeguiLayerSpecification;

template <>
inline VALUE wrap< CEGUI::LayerSpecification >(CEGUI::LayerSpecification *section )
{
	if(section==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiLayerSpecification, NULL, NULL, section);
}
template <>
inline CEGUI::LayerSpecification* wrap< CEGUI::LayerSpecification* >(const VALUE &vsection)
{
	return unwrapPtr<CEGUI::LayerSpecification>(vsection, rb_cCeguiLayerSpecification);
}
#endif /* __RubyCeguiLayerSpecification_H__ */
