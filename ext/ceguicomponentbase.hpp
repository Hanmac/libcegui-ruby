/*
 * ceguicomponentbase.hpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiComponentBase_H__
#define __RubyCeguiComponentBase_H__

#include "ceguiframecomponent.hpp"


void Init_CeguiComponentBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiComponentBase;


template <>
inline VALUE wrap< CEGUI::FalagardComponentBase >(CEGUI::FalagardComponentBase *componentbase )
{
	CEGUI::FrameComponent *framecomponent = dynamic_cast<CEGUI::FrameComponent*>(componentbase);
	if(framecomponent)
		return wrap(framecomponent);

	return Data_Wrap_Struct(rb_cCeguiComponentBase, NULL, NULL, componentbase);
}

template <>
inline CEGUI::FalagardComponentBase* wrap< CEGUI::FalagardComponentBase* >(const VALUE &vcomponentbase)
{
	if (rb_obj_is_kind_of(vcomponentbase, rb_cCeguiComponentBase)){
		CEGUI::FalagardComponentBase *componentbase;
		Data_Get_Struct( vcomponentbase, CEGUI::FalagardComponentBase, componentbase);
		return componentbase;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiComponentBase),rb_obj_classname(vcomponentbase));
		return NULL;
	}
}
#endif /* __RubyCeguiComponentBase_H__ */
