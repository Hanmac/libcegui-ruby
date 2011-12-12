/*
 * ceguitabcontrol.hpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiTabControl_H__
#define __RubyCeguiTabControl_H__

#include "main.hpp"
void Init_CeguiTabControl(VALUE rb_mCegui);
extern VALUE rb_cCeguiTabControl;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::TabControl >(CEGUI::TabControl *tabcontrol )
{
	return RubyWindowHolder::get(tabcontrol,rb_cCeguiTabControl);
}

template <>
inline CEGUI::TabControl* wrap< CEGUI::TabControl* >(const VALUE &vtabcontrol)
{
	if (rb_obj_is_kind_of(vtabcontrol, rb_cCeguiTabControl)){
		return (CEGUI::TabControl*)(wrap< CEGUI::Window* >(vtabcontrol));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiTabControl),rb_obj_classname(vtabcontrol));
		return NULL;
	}
}
#endif /* __RubyCeguiTabControl_H__ */
