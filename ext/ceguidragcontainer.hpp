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
	if (rb_obj_is_kind_of(vdragcontainer, rb_cCeguiDragContainer)){
		return (CEGUI::DragContainer*)(wrap< CEGUI::Window* >(vdragcontainer));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiDragContainer),rb_obj_classname(vdragcontainer));
		return NULL;
	}
}
#endif /* __RubyCeguiDragContainer_H__ */

