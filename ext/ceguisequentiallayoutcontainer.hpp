/*
 * ceguisequentiallayoutcontainer.hpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiSequentialLayoutContainer_H__
#define __RubyCeguiSequentialLayoutContainer_H__

#include "main.hpp"
void Init_CeguiSequentialLayoutContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiSequentialLayoutContainer;

#include "ceguihorizontallayoutcontainer.hpp"
#include "ceguiverticallayoutcontainer.hpp"

template <>
inline VALUE wrap< CEGUI::SequentialLayoutContainer >(CEGUI::SequentialLayoutContainer *layoutcontainer )
{
	if(layoutcontainer==NULL)
		return Qnil;

	CEGUI::HorizontalLayoutContainer *horizontal = dynamic_cast<CEGUI::HorizontalLayoutContainer*>(layoutcontainer);
	if(horizontal)
		return wrap(horizontal);
	CEGUI::VerticalLayoutContainer *vertical = dynamic_cast<CEGUI::VerticalLayoutContainer*>(layoutcontainer);
	if(vertical)
		return wrap(vertical);

	return RubyWindowHolder::get(layoutcontainer,rb_cCeguiSequentialLayoutContainer);
}

template <>
inline CEGUI::SequentialLayoutContainer* wrap< CEGUI::SequentialLayoutContainer* >(const VALUE &vlayoutcontainer)
{
	if (rb_obj_is_kind_of(vlayoutcontainer, rb_cCeguiSequentialLayoutContainer)){
		return (CEGUI::SequentialLayoutContainer*)(wrap< CEGUI::Window* >(vlayoutcontainer));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiSequentialLayoutContainer),rb_obj_classname(vlayoutcontainer));
		return NULL;
	}
}
#endif /* __RubyCeguiSequentialLayoutContainer_H__ */
