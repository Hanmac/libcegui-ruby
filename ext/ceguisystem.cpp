#include "ceguisystem.hpp"

#include "ceguiresourceprovider.hpp"
#include "ceguiwindow.hpp"
#include "ceguieventset.hpp"


#include "ceguixmlparser.hpp"

#define _self CEGUI::System::getSingletonPtr()

VALUE rb_mCeguiSystem;

/*
*/
VALUE CeguiSystem_getResourceProvider(VALUE self)
{
	return wrap(_self->getResourceProvider());
}
/*
*/
VALUE CeguiSystem_getGuiSheet(VALUE self)
{
	return wrap(_self->getGUISheet());
}
/*
*/
VALUE CeguiSystem_setGuiSheet(VALUE self,VALUE val)
{
	_self->setGUISheet(wrap<CEGUI::Window*>(val));
	return val;
}
/*
*/
VALUE CeguiSystem_getModalTarget(VALUE self)
{
	return wrap(_self->getModalTarget());
}
/*
*/
VALUE CeguiSystem_setModalTarget(VALUE self,VALUE val)
{
	_self->setModalTarget(wrap<CEGUI::Window*>(val));
	return val;
}
/*
*/
VALUE CeguiSystem_getDefaultTooltip(VALUE self)
{
	return wrap(_self->getDefaultTooltip());
}
/*
*/
VALUE CeguiSystem_setDefaultTooltip(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cString))
		_self->setDefaultTooltip(wrap<CEGUI::String>(val));
	else
		_self->setDefaultTooltip(wrap<CEGUI::Tooltip*>(val));
	return val;
}
/*
*/
VALUE CeguiSystem_getXMLParser(VALUE self)
{
	return wrap(_self->getXMLParser());
}
/*
*/
VALUE CeguiSystem_setXMLParser(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cString))
		_self->setXMLParser(wrap<CEGUI::String>(val));
	else
		_self->setXMLParser(wrap<CEGUI::XMLParser*>(val));
	return val;
}


/*
*/
VALUE CeguiSystem_setDefaultXMLParserName(VALUE self,VALUE val)
{
	CEGUI::System::setDefaultXMLParserName(wrap<CEGUI::String>(val));
 	return val;
}
/*
*/ 	
VALUE CeguiSystem_getDefaultXMLParserName(VALUE self)
{
	return wrap(CEGUI::System::getDefaultXMLParserName());
}
/*
*/
VALUE CeguiSystem_setDefaultImageCodecName(VALUE self,VALUE val)
{
	CEGUI::System::setDefaultImageCodecName(wrap<CEGUI::String>(val));
 	return val;
}
/*
*/
VALUE CeguiSystem_getDefaultImageCodecName(VALUE self)
{
	return wrap(CEGUI::System::getDefaultImageCodecName());
}
/*
*/
void Init_CeguiSystem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
#endif
	
	rb_mCeguiSystem = rb_define_module_under(rb_mCegui,"System");
	rb_define_singleton_method(rb_mCeguiSystem,"resourceProvider",RUBY_METHOD_FUNC(CeguiSystem_getResourceProvider),0);

	rb_extend_object(rb_mCeguiSystem,rb_mCeguiEventSet);

	rb_define_singleton_method(rb_mCeguiSystem,"guiSheet",RUBY_METHOD_FUNC(CeguiSystem_getGuiSheet),0);
	rb_define_singleton_method(rb_mCeguiSystem,"guiSheet=",RUBY_METHOD_FUNC(CeguiSystem_setGuiSheet),1);

	rb_define_singleton_method(rb_mCeguiSystem,"modalTarget",RUBY_METHOD_FUNC(CeguiSystem_getModalTarget),0);
	rb_define_singleton_method(rb_mCeguiSystem,"modalTarget=",RUBY_METHOD_FUNC(CeguiSystem_setModalTarget),1);

	rb_define_singleton_method(rb_mCeguiSystem,"defaultTooltip",RUBY_METHOD_FUNC(CeguiSystem_getDefaultTooltip),0);
	rb_define_singleton_method(rb_mCeguiSystem,"defaultTooltip=",RUBY_METHOD_FUNC(CeguiSystem_setDefaultTooltip),1);

	rb_define_singleton_method(rb_mCeguiSystem,"xmlparser",RUBY_METHOD_FUNC(CeguiSystem_getXMLParser),0);
	rb_define_singleton_method(rb_mCeguiSystem,"xmlparser=",RUBY_METHOD_FUNC(CeguiSystem_setXMLParser),1);


	
	rb_define_singleton_method(rb_mCeguiSystem,"defaultxmlparser",RUBY_METHOD_FUNC(CeguiSystem_getDefaultXMLParserName),0);
	rb_define_singleton_method(rb_mCeguiSystem,"defaultxmlparser=",RUBY_METHOD_FUNC(CeguiSystem_setDefaultXMLParserName),1);
	
	rb_define_singleton_method(rb_mCeguiSystem,"defaultimagecodec",RUBY_METHOD_FUNC(CeguiSystem_getDefaultImageCodecName),0);
	rb_define_singleton_method(rb_mCeguiSystem,"defaultimagecodec=",RUBY_METHOD_FUNC(CeguiSystem_setDefaultImageCodecName),1);
}
