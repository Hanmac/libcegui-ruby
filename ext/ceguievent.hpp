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
	if (rb_obj_is_kind_of(vevent, rb_cCeguiEvent)){
		CEGUI::Event *event;
		Data_Get_Struct( vevent, CEGUI::Event, event);
		return event;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiEvent),rb_obj_classname(vevent));
		return NULL;
	}
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
	bool operator()(const CEGUI::EventArgs& e);
	~Subscriberfunc();
private:
	VALUE value;
};
#endif /* __RubyCeguiEvent_H__ */
