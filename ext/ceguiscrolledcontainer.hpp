/*
 * ceguiscrolledcontainer.hpp
 *
 *  Created on: 04.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiScrolledContainer_H__
#define __RubyCeguiScrolledContainer_H__

#include "main.hpp"
void Init_CeguiScrolledContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiScrolledContainer;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::ScrolledContainer >(CEGUI::ScrolledContainer *scrolledcontainer )
{
	return RubyWindowHolder::get(scrolledcontainer,rb_cCeguiScrolledContainer);
}

template <>
inline CEGUI::ScrolledContainer* wrap< CEGUI::ScrolledContainer* >(const VALUE &vscrolledcontainer)
{
	return unwrapWindow<CEGUI::ScrolledContainer>(vscrolledcontainer, rb_cCeguiScrolledContainer);
}
#endif /* __RubyCeguiScrolledContainer_H__ */

