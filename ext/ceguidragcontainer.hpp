/*
 * ceguidragcontainer.hpp
 *
 *  Created on: 04.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiDragContainer_H__
#define __RubyCeguiDragContainer_H__

#include "main.hpp"
void Init_CeguiDragContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiDragContainer;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::DragContainer >(CEGUI::DragContainer *dragcontainer )
{
	return RubyWindowHolder::get(dragcontainer,rb_cCeguiDragContainer);
}

template <>
inline CEGUI::DragContainer* wrap< CEGUI::DragContainer* >(const VALUE &vdragcontainer)
{
	return unwrapWindow<CEGUI::DragContainer>(vdragcontainer, rb_cCeguiDragContainer);
}
#endif /* __RubyCeguiDragContainer_H__ */

