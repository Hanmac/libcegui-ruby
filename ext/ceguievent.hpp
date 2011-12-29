#ifndef __RubyCeguiEvent_H__
#define __RubyCeguiEvent_H__

#include "main.hpp"
void Init_CeguiEvent(VALUE rb_mCegui);
extern VALUE rb_cCeguiEvent;

extern VALUE subscriberholder;

template <>
inline VALUE wrap< CEGUI::Event >(CEGUI::Event *event )
{
	if(event==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiEvent, NULL, NULL, event);
}

template <>
inline CEGUI::Event* wrap< CEGUI::Event* >(const VALUE &vevent)
{
	return unwrapPtr<CEGUI::Event>(vevent, rb_cCeguiEvent);
}
/*
template <>
inline CEGUI::Event wrap< CEGUI::Event >(const VALUE &vevent)
{
	return *wrap< CEGUI::Event* >(vevent);
}
*/
class Subscriberfunc
{
public:
	Subscriberfunc(VALUE val);
	~Subscriberfunc();
	bool operator()(const CEGUI::EventArgs& e);
private:
	VALUE value;
};
#endif /* __RubyCeguiEvent_H__ */
