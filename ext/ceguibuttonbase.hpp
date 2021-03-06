#ifndef __RubyCeguiButtonBase_H__
#define __RubyCeguiButtonBase_H__

#include "main.hpp"
void Init_CeguiButtonBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiButtonBase;

#include "ceguitabbutton.hpp"
#include "ceguipushbutton.hpp"
#include "ceguicheckbox.hpp"
template <>
inline VALUE wrap< CEGUI::ButtonBase >(CEGUI::ButtonBase *buttonbase )
{
	if(buttonbase==NULL)
		return Qnil;

	CEGUI::TabButton *tab = dynamic_cast<CEGUI::TabButton*>(buttonbase);
	if(tab)
		return wrap(tab);

	CEGUI::Thumb *thumb = dynamic_cast<CEGUI::Thumb*>(buttonbase);
	if(thumb)
		return wrap(thumb);

	CEGUI::PushButton *pushbotton = dynamic_cast<CEGUI::PushButton*>(buttonbase);
	if(pushbotton)
		return wrap(pushbotton);

	CEGUI::Checkbox *checkbox = dynamic_cast<CEGUI::Checkbox*>(buttonbase);
	if(checkbox)
		return wrap(checkbox);

	return RubyWindowHolder::get(buttonbase,rb_cCeguiButtonBase);
}

template <>
inline CEGUI::ButtonBase* wrap< CEGUI::ButtonBase* >(const VALUE &vbuttonbase)
{
	return unwrapWindow<CEGUI::ButtonBase>(vbuttonbase, rb_cCeguiButtonBase);
}
#endif /* __RubyCeguiButtonBase_H__ */
