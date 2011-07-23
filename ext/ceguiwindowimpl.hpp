#ifndef __RubyCeguiWindowImpl_H__
#define __RubyCeguiWindowImpl_H__

#include "main.hpp"
struct RubyWindowHolder
{
	CEGUI::Window* window;
	VALUE ruby;

};
extern VALUE rb_cCeguiWindow;
extern std::map<CEGUI::Window*,RubyWindowHolder*> rubywindowholder;

int ruby_window_destroyed_callback(const CEGUI::EventArgs &arg);
void ruby_bootstrap();
template <>
inline RubyWindowHolder* wrap< RubyWindowHolder* >(const VALUE &vwindow)
{
	if (rb_obj_is_kind_of(vwindow, rb_cCeguiWindow)){
		RubyWindowHolder *window;
		Data_Get_Struct( vwindow, RubyWindowHolder, window);
		return window;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiWindow),rb_obj_classname(vwindow));
		return NULL;
	}
}

template <>
inline CEGUI::Window* wrap< CEGUI::Window* >(const VALUE &vwindow)
{
	CEGUI::Window* window = wrap<RubyWindowHolder*>(vwindow)->window;
	if(window==NULL)
		rb_raise(rb_eTypeError,"calling a function of a destroyed Object!");
	return window;
}
#endif /* __RubyCeguiWindowImpl_H__ */
