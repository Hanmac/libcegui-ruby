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
	return RubyWindowHolder::get(pushbutton,rb_cCeguiPushButton);
}

template <>
inline CEGUI::PushButton* wrap< CEGUI::PushButton* >(const VALUE &vpushbutton)
{
	return unwrapWindow<CEGUI::PushButton>(vpushbutton, rb_cCeguiPushButton);
}
#endif /* __RubyCeguiPushButton_H__ */
