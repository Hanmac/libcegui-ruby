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
	if (rb_obj_is_kind_of(vclippedcontainer, rb_cCeguiClippedContainer)){
		return (CEGUI::ClippedContainer*)(wrap< CEGUI::Window* >(vclippedcontainer));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiClippedContainer),rb_obj_classname(vclippedcontainer));
		return NULL;
	}
}
#endif /* __RubyCeguiClippedContainer_H__ */

