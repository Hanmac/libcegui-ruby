/*
 * ceguiclippedcontainer.hpp
 *
 *  Created on: 02.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiClippedContainer_H__
#define __RubyCeguiClippedContainer_H__

#include "main.hpp"
void Init_CeguiClippedContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiClippedContainer;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::ClippedContainer >(CEGUI::ClippedContainer *clippedcontainer )
{
	return RubyWindowHolder::get(clippedcontainer,rb_cCeguiClippedContainer);
}

template <>
inline CEGUI::ClippedContainer* wrap< CEGUI::ClippedContainer* >(const VALUE &vclippedcontainer)
{
	return unwrapWindow<CEGUI::ClippedContainer>(vclippedcontainer, rb_cCeguiClippedContainer);
}
#endif /* __RubyCeguiClippedContainer_H__ */

