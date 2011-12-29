#ifndef __RubyCeguiScrollbar_H__
#define __RubyCeguiScrollbar_H__

#include "main.hpp"
void Init_CeguiScrollbar(VALUE rb_mCegui);
extern VALUE rb_cCeguiScrollbar;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Scrollbar >(CEGUI::Scrollbar *scrollbar )
{
	return RubyWindowHolder::get(scrollbar,rb_cCeguiScrollbar);
}

template <>
inline CEGUI::Scrollbar* wrap< CEGUI::Scrollbar* >(const VALUE &vscrollbar)
{
	return unwrapWindow<CEGUI::Scrollbar>(vscrollbar, rb_cCeguiScrollbar);
}
#endif /* __RubyCeguiScrollbar_H__ */
