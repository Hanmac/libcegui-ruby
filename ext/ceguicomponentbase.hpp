/*
 * ceguicomponentbase.hpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiComponentBase_H__
#define __RubyCeguiComponentBase_H__

#include "ceguiframecomponent.hpp"
#include "ceguiimagerycomponent.hpp"
#include "ceguitextcomponent.hpp"
void Init_CeguiComponentBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiComponentBase;


template <>
inline VALUE wrap< CEGUI::FalagardComponentBase >(CEGUI::FalagardComponentBase *componentbase )
{
	CEGUI::FrameComponent *framecomponent = dynamic_cast<CEGUI::FrameComponent*>(componentbase);
	if(framecomponent)
		return wrap(framecomponent);

	CEGUI::ImageryComponent *imagerycomponent = dynamic_cast<CEGUI::ImageryComponent*>(componentbase);
	if(imagerycomponent)
		return wrap(imagerycomponent);

	CEGUI::TextComponent *textcomponent = dynamic_cast<CEGUI::TextComponent*>(componentbase);
	if(textcomponent)
		return wrap(textcomponent);

	return Data_Wrap_Struct(rb_cCeguiComponentBase, NULL, NULL, componentbase);
}

template <>
inline CEGUI::FalagardComponentBase* wrap< CEGUI::FalagardComponentBase* >(const VALUE &vcomponentbase)
{
	return unwrapPtr<CEGUI::FalagardComponentBase>(vcomponentbase, rb_cCeguiComponentBase);
}
#endif /* __RubyCeguiComponentBase_H__ */
