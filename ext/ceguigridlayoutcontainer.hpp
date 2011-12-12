/*
 * ceguigridlayoutcontainer.hpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiGridLayoutContainer_H__
#define __RubyCeguiGridLayoutContainer_H__

#include "main.hpp"
void Init_CeguiGridLayoutContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiGridLayoutContainer;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::GridLayoutContainer >(CEGUI::GridLayoutContainer *layoutcontainer )
{
	return RubyWindowHolder::get(layoutcontainer,rb_cCeguiGridLayoutContainer);
}

template <>
inline CEGUI::GridLayoutContainer* wrap< CEGUI::GridLayoutContainer* >(const VALUE &vlayoutcontainer)
{
	if (rb_obj_is_kind_of(vlayoutcontainer, rb_cCeguiGridLayoutContainer)){
		return (CEGUI::GridLayoutContainer*)(wrap< CEGUI::Window* >(vlayoutcontainer));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiGridLayoutContainer),rb_obj_classname(vlayoutcontainer));
		return NULL;
	}
}
#endif /* __RubyCeguiGridLayoutContainer_H__ */
