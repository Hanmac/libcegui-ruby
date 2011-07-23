#ifndef __RubyCeguiPushButton_H__
#define __RubyCeguiPushButton_H__

#include "main.hpp"
void Init_CeguiPushButton(VALUE rb_mCegui);
extern VALUE rb_cCeguiPushButton;

#include "ceguithumb.hpp"

template <>
inline VALUE wrap< CEGUI::PushButton >(CEGUI::PushButton *pushbutton )
{
	if(pushbutton==NULL)
		return Qnil;
	CEGUI::Thumb *thumb = dynamic_cast<CEGUI::Thumb*>(pushbutton);
	if(thumb)
		return wrap(thumb);
	return Data_Wrap_Struct(rb_cCeguiPushButton, NULL, NULL, pushbutton);
}

template <>
inline CEGUI::PushButton* wrap< CEGUI::PushButton* >(const VALUE &vpushbutton)
{
	if (rb_obj_is_kind_of(vpushbutton, rb_cCeguiPushButton)){
		CEGUI::PushButton *pushbutton;
		Data_Get_Struct( vpushbutton, CEGUI::PushButton, pushbutton);
		return pushbutton;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiPushButton),rb_obj_classname(vpushbutton));
		return NULL;
	}
}
#endif /* __RubyCeguiPushButton_H__ */
