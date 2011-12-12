/*
 * ceguiverticallayoutcontainer.hpp
 *
 *  Created on: 11.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiVerticalLayoutContainer_H__
#define __RubyCeguiVerticalLayoutContainer_H__

#include "main.hpp"
void Init_CeguiVerticalLayoutContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiVerticalLayoutContainer;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::VerticalLayoutContainer >(CEGUI::VerticalLayoutContainer *layoutcontainer )
{
	return RubyWindowHolder::get(layoutcontainer,rb_cCeguiVerticalLayoutContainer);
}

template <>
inline CEGUI::VerticalLayoutContainer* wrap< CEGUI::VerticalLayoutContainer* >(const VALUE &vlayoutcontainer)
{
	if (rb_obj_is_kind_of(vlayoutcontainer, rb_cCeguiVerticalLayoutContainer)){
		return (CEGUI::VerticalLayoutContainer*)(wrap< CEGUI::Window* >(vlayoutcontainer));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiVerticalLayoutContainer),rb_obj_classname(vlayoutcontainer));
		return NULL;
	}
}
#endif /* __RubyCeguiVerticalLayoutContainer_H__ */
