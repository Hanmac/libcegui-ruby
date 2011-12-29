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
	return unwrapWindow<CEGUI::HorizontalLayoutContainer>(vlayoutcontainer, rb_cCeguiHorizontalLayoutContainer);
}
#endif /* __RubyCeguiHorizontalLayoutContainer_H__ */

