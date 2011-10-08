#include "ceguixmlhandler.hpp"

VALUE rb_cCeguiXMLHandler;


void RubyXMLHandler::elementStart(const CEGUI::String &element, const CEGUI::XMLAttributes &attributes)
{
	rb_funcall(this->value,rb_intern("elementStart"),2,wrap(element),wrap(attributes));
}
void RubyXMLHandler::elementEnd(const CEGUI::String &element)
{
	rb_funcall(this->value,rb_intern("elementEnd"),1,wrap(element));
}
void RubyXMLHandler::text(const CEGUI::String &text)
{
	rb_funcall(this->value,rb_intern("text"),1,wrap(text));
}
const CEGUI::String& RubyXMLHandler::getDefaultResourceGroup() const
{
	return temp.assign(wrap<CEGUI::String>(rb_funcall(this->value,rb_intern("getDefaultResourceGroup"),0)));
}


VALUE CeguiXMLHandler_alloc(VALUE self)
{
	return wrap(new RubyXMLHandler);
}

void Init_CeguiXMLHandler(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiXMLHandler = rb_define_class_under(rb_mCegui,"XMLHandler",rb_cObject);
	rb_define_alloc_func(rb_cCeguiXMLHandler,CeguiXMLHandler_alloc);

}
