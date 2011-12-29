/*
 * ceguiimagerycomponent.hpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiImageryComponent_H__
#define __RubyCeguiImageryComponent_H__

#include "main.hpp"
void Init_CeguiImageryComponent(VALUE rb_mCegui);
extern VALUE rb_cCeguiImageryComponent;


template <>
inline VALUE wrap< CEGUI::ImageryComponent >(CEGUI::ImageryComponent *imagerycomponent )
{
	return Data_Wrap_Struct(rb_cCeguiImageryComponent, NULL, NULL, imagerycomponent);
}

template <>
inline CEGUI::ImageryComponent* wrap< CEGUI::ImageryComponent* >(const VALUE &vimagerycomponent)
{
	return unwrapPtr<CEGUI::ImageryComponent>(vimagerycomponent, rb_cCeguiImageryComponent);
}
#endif /* __RubyCeguiImageryComponent_H__ */
