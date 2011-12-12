#ifndef __RubyCeguiEditbox_H__
#define __RubyCeguiEditbox_H__

#include "main.hpp"
void Init_CeguiEditbox(VALUE rb_mCegui);
extern VALUE rb_cCeguiEditbox;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Editbox >(CEGUI::Editbox *editbox )
{
	return RubyWindowHolder::get(editbox,rb_cCeguiEditbox);
}

template <>
inline CEGUI::Editbox* wrap< CEGUI::Editbox* >(const VALUE &veditbox)
{
	if (rb_obj_is_kind_of(veditbox, rb_cCeguiEditbox)){
		return (CEGUI::Editbox*)(wrap< CEGUI::Window* >(veditbox));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiEditbox),rb_obj_classname(veditbox));
		return NULL;
	}
}
#endif /* __RubyCeguiEditbox_H__ */
