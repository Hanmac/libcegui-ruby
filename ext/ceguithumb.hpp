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
	if (rb_obj_is_kind_of(vthumb, rb_cCeguiThumb)){
		return (CEGUI::Thumb*)(wrap< CEGUI::Window* >(vthumb));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiThumb),rb_obj_classname(vthumb));
		return NULL;
	}
}
#endif /* __RubyCeguiThumb_H__ */
