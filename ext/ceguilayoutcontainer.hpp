#ifndef __RubyCeguiLayoutContainer_H__
#define __RubyCeguiLayoutContainer_H__

#include "main.hpp"
void Init_CeguiLayoutContainer(VALUE rb_mCegui);
extern VALUE rb_cCeguiLayoutContainer;

#include "ceguisequentiallayoutcontainer.hpp"
#include "ceguigridlayoutcontainer.hpp"

template <>
inline VALUE wrap< CEGUI::LayoutContainer >(CEGUI::LayoutContainer *layoutcontainer )
{
	if(layoutcontainer==NULL)
		return Qnil;

	CEGUI::SequentialLayoutContainer *sequential = dynamic_cast<CEGUI::SequentialLayoutContainer*>(layoutcontainer);
	if(sequential)
		return wrap(sequential);
	CEGUI::GridLayoutContainer *grid = dynamic_cast<CEGUI::GridLayoutContainer*>(layoutcontainer);
	if(grid)
		return wrap(grid);

	return RubyWindowHolder::get(layoutcontainer,rb_cCeguiLayoutContainer);
}

template <>
inline CEGUI::LayoutContainer* wrap< CEGUI::LayoutContainer* >(const VALUE &vlayoutcontainer)
{
	if (rb_obj_is_kind_of(vlayoutcontainer, rb_cCeguiLayoutContainer)){
		return (CEGUI::LayoutContainer*)(wrap< CEGUI::Window* >(vlayoutcontainer));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiLayoutContainer),rb_obj_classname(vlayoutcontainer));
		return NULL;
	}
}
#endif /* __RubyCeguiLayoutContainer_H__ */
