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
	return unwrapWindow<CEGUI::VerticalLayoutContainer>(vlayoutcontainer, rb_cCeguiVerticalLayoutContainer);
}
#endif /* __RubyCeguiVerticalLayoutContainer_H__ */
