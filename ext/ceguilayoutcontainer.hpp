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
	return unwrapWindow<CEGUI::LayoutContainer>(vlayoutcontainer, rb_cCeguiLayoutContainer);
}
#endif /* __RubyCeguiLayoutContainer_H__ */
