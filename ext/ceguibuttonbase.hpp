#ifndef __RubyCeguiButtonBase_H__
#define __RubyCeguiButtonBase_H__

#include "main.hpp"
void Init_CeguiButtonBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiButtonBase;

#include "ceguipushbutton.hpp"
#include "ceguicheckbox.hpp"
template <>
inline VALUE wrap< CEGUI::ButtonBase >(CEGUI::ButtonBase *buttonbase )
{
	if(buttonbase==NULL)
		return Qnil;
	CEGUI::Thumb *thumb = dynamic_cast<CEGUI::Thumb*>(buttonbase);
	if(thumb)
		return wrap(thumb);
	CEGUI::PushButton *pushbotton = dynamic_cast<CEGUI::PushButton*>(buttonbase);
	if(pushbotton)
		return wrap(pushbotton);
	CEGUI::Checkbox *checkbox = dynamic_cast<CEGUI::Checkbox*>(buttonbase);
	if(checkbox)
		return wrap(checkbox);

	return Qnil;//Data_Wrap_Struct(rb_cCeguiButtonBase, NULL, NULL, buttonbase);
}

template <>
inline CEGUI::ButtonBase* wrap< CEGUI::ButtonBase* >(const VALUE &vbuttonbase)
{
	if (rb_obj_is_kind_of(vbuttonbase, rb_cCeguiButtonBase)){
		return (CEGUI::ButtonBase*)(wrap< CEGUI::Window* >(vbuttonbase));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiButtonBase),rb_obj_classname(vbuttonbase));
		return NULL;
	}
}
#endif /* __RubyCeguiButtonBase_H__ */
