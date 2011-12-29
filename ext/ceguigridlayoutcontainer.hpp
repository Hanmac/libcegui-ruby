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
	return unwrapWindow<CEGUI::GridLayoutContainer>(vlayoutcontainer, rb_cCeguiGridLayoutContainer);
}
#endif /* __RubyCeguiGridLayoutContainer_H__ */
