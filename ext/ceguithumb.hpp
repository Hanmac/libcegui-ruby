#ifndef __RubyCeguiThumb_H__
#define __RubyCeguiThumb_H__

#include "main.hpp"
void Init_CeguiThumb(VALUE rb_mCegui);
extern VALUE rb_cCeguiThumb;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Thumb >(CEGUI::Thumb *thumb )
{
	return RubyWindowHolder::get(thumb,rb_cCeguiThumb);
}

template <>
inline CEGUI::Thumb* wrap< CEGUI::Thumb* >(const VALUE &vthumb)
{
	return unwrapWindow<CEGUI::Thumb>(vthumb, rb_cCeguiThumb);
}
#endif /* __RubyCeguiThumb_H__ */
