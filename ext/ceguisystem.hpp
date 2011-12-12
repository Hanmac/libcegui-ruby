#ifndef __RubyCeguiSystem_H__
#define __RubyCeguiSystem_H__

#include "main.hpp"

void Init_CeguiSystem(VALUE rb_mCegui);
extern VALUE rb_mCeguiSystem;



template <>
inline CEGUI::System* wrap< CEGUI::System* >(const VALUE &obj)
{
	CEGUI::System* temp = CEGUI::System::getSingletonPtr();
	if(temp == NULL)
		rb_raise(rb_eRuntimeError,"%s is not created!",rb_class2name(rb_mCeguiSystem));
	return temp;
}
//template <>
//inline VALUE wrap< CEGUI::MouseButton >(CEGUI::MouseButton &button )
//{
//	switch(button){
//	case CEGUI::LeftButton:
//		return ID2SYM(rb_intern("LeftButton"));
//	case CEGUI::RightButton:
//		return ID2SYM(rb_intern("RightButton"));
//	case CEGUI::MiddleButton:
//		return ID2SYM(rb_intern("MiddleButton"));
//	}
//}

template <>
inline CEGUI::MouseButton wrap< CEGUI::MouseButton >(const VALUE &vbutton)
{
	ID result = SYM2ID(vbutton);
	if(result == rb_intern("LeftButton")){
		return CEGUI::LeftButton;
	}if(result == rb_intern("RightButton"))
		return CEGUI::RightButton;
	if(result == rb_intern("MiddleButton"))
		return CEGUI::MiddleButton;
	return CEGUI::LeftButton;
}
#endif /* __RubyCeguiRenderer_H__ */
