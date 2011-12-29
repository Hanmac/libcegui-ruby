#ifndef __RubyCeguiWindowImpl_H__
#define __RubyCeguiWindowImpl_H__

#include "main.hpp"
class RubyWindowHolder
{
public:
	RubyWindowHolder(CEGUI::Window* wnd,VALUE klass);
	CEGUI::Window* window;
	VALUE ruby;
	static VALUE get(CEGUI::Window* obj,VALUE klass);
};

extern VALUE rb_cCeguiWindow;
extern std::map<CEGUI::Window*,RubyWindowHolder*> rubywindowholder;
extern VALUE rb_windowholder;

int ruby_window_destroyed_callback(const CEGUI::EventArgs &arg);
void ruby_bootstrap();

template <>
inline RubyWindowHolder* wrap< RubyWindowHolder* >(const VALUE &vwindow)
{
	return unwrapPtr<RubyWindowHolder>(vwindow, rb_cCeguiWindow);
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
