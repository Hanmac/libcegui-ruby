/*
 * ceguihorizontallayoutcontainer.hpp
 *
 *  Created on: 11.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiHorizontalLayoutContainer_H__
#define __RubyCeguiHorizontalLayoutContainer_H__

#include "main.hpp"
void Init_CeguiHorizontalLayoutContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiHorizontalLayoutContainer;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::HorizontalLayoutContainer >(CEGUI::HorizontalLayoutContainer *layoutcontainer )
{
	return RubyWindowHolder::get(layoutcontainer,rb_cCeguiHorizontalLayoutContainer);
}

template <>
inline CEGUI::HorizontalLayoutContainer* wrap< CEGUI::HorizontalLayoutContainer* >(const VALUE &vlayoutcontainer)
{
	if (rb_obj_is_kind_of(vlayoutcontainer, rb_cCeguiHorizontalLayoutContainer)){
		return (CEGUI::HorizontalLayoutContainer*)(wrap< CEGUI::Window* >(vlayoutcontainer));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiHorizontalLayoutContainer),rb_obj_classname(vlayoutcontainer));
		return NULL;
	}
}
#endif /* __RubyCeguiHorizontalLayoutContainer_H__ */

