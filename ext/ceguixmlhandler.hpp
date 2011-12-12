#ifndef __RubyCeguiXMLHandler_H__
#define __RubyCeguiXMLHandler_H__

#include "main.hpp"

class RubyXMLHandler : public CEGUI::XMLHandler{
public:

	void elementStart(const CEGUI::String &element, const CEGUI::XMLAttributes &attributes);
	void elementEnd (const CEGUI::String &element);
	void text(const CEGUI::String &text);
	const CEGUI::String& getDefaultResourceGroup() const;
	VALUE value;
	
	CEGUI::String mutable temp;
};

void Init_CeguiXMLHandler(VALUE rb_mCegui);
extern VALUE rb_cCeguiXMLHandler;

template <>
inline VALUE wrap< RubyXMLHandler >(RubyXMLHandler *handler )
{
	if(handler==NULL)
		return Qnil;
	if(handler->value==Qnil)
		handler->value = Data_Wrap_Struct(rb_cCeguiXMLHandler, NULL, free, handler);
	return handler->value;
}
template <>
inline CEGUI::XMLHandler* wrap< CEGUI::XMLHandler* >(const VALUE &vhandler)
{
	if (rb_obj_is_kind_of(vhandler, rb_cCeguiXMLHandler)){
		CEGUI::XMLHandler *handler;
		Data_Get_Struct( vhandler, CEGUI::XMLHandler, handler);
		return handler;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiXMLHandler),rb_obj_classname(vhandler));
		return NULL;
	}
}
/*
template <>
inline CEGUI::XMLHandler wrap< CEGUI::XMLHandler >(const VALUE &vhandler)
{
	return *wrap< CEGUI::XMLHandler* >(vhandler);
}
*/
#endif /* __RubyCeguiXMLHandler_H__ */
