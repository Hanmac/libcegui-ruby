#ifndef __RubyCeguiTooltip_H__
#define __RubyCeguiTooltip_H__

#include "main.hpp"
void Init_CeguiTooltip(VALUE rb_mCegui);
extern VALUE rb_cCeguiTooltip;


#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Tooltip >(CEGUI::Tooltip *tooltip )
{
	return RubyWindowHolder::get(tooltip,rb_cCeguiTooltip);
}

template <>
inline CEGUI::Tooltip* wrap< CEGUI::Tooltip* >(const VALUE &vtooltip)
{
	return unwrapWindow<CEGUI::Tooltip>(vtooltip, rb_cCeguiTooltip);
}
#endif /* __RubyCeguiTooltip_H__ */
