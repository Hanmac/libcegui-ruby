#include "ceguisystem.hpp"

#include "ceguiresourceprovider.hpp"
#include "ceguiwindow.hpp"
#include "ceguifont.hpp"
#include "ceguieventset.hpp"

#include "ceguiexception.hpp"

#include "ceguixmlparser.hpp"
#include "ceguiimagecodec.hpp"
#include "ceguiscriptmodule.hpp"

#include "ceguirenderer.hpp"

#define _self CEGUI::System::getSingletonPtr()

VALUE rb_cCeguiSystem,vSystem;

macro_attr(System,GUISheet,CEGUI::Window*)
macro_attr(System,ModalTarget,CEGUI::Window*)
macro_attr(System,ScriptingModule,CEGUI::ScriptModule*)

macro_attr(System,DefaultMouseCursor,CEGUI::Image*)

/*
*/
VALUE CeguiSystem_getResourceProvider(VALUE self)
{
	return wrap(_self->getResourceProvider());
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
VALUE CeguiSystem_getDefaultFont(VALUE self)
{
	return wrap(_self->getDefaultFont());
}
/*
*/
VALUE CeguiSystem_setDefaultFont(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cString))
		_self->setDefaultFont(wrap<CEGUI::String>(val));
	else
		_self->setDefaultFont(wrap<CEGUI::Font*>(val));
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
	try{
		if(rb_obj_is_kind_of(val, rb_cString))
			_self->setXMLParser(wrap<CEGUI::String>(val));
		else
			_self->setXMLParser(wrap<CEGUI::XMLParser*>(val));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
	}
	return val;
}

/*
*/
VALUE CeguiSystem_renderGUI(VALUE self)
{
	_self->renderGUI();
	return self;
}
/*
*/
VALUE CeguiSystem_getImageCodec(VALUE self)
{
	return wrap_imagecodec(_self->getImageCodec());
}
/*
*/
VALUE CeguiSystem_setImageCodec(VALUE self,VALUE val)
{
	try{
		if(rb_obj_is_kind_of(val, rb_cString))
			_self->setImageCodec(wrap<CEGUI::String>(val));
		else
			_self->setImageCodec(wrap_imagecodec(val));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
	}
	return val;
}

/*
*/
VALUE CeguiSystem_signalRedraw(VALUE self)
{
	_self->signalRedraw();
	return self;
}

/*
*/
VALUE CeguiSystem_isRedrawRequested(VALUE self)
{
	return wrap(_self->isRedrawRequested());
}

/*
*/
VALUE CeguiSystem_injectMousePosition(VALUE self,VALUE x,VALUE y)
{
	return wrap(_self->injectMousePosition(NUM2DBL(x),NUM2DBL(y)));
}
/*
*/
VALUE CeguiSystem_injectMouseMove(VALUE self,VALUE x,VALUE y)
{
	return wrap(_self->injectMouseMove(NUM2DBL(x),NUM2DBL(y)));
}

/*
*/
VALUE CeguiSystem_injectMouseButtonDown(VALUE self,VALUE button)
{
	return wrap(_self->injectMouseButtonDown(wrap<CEGUI::MouseButton>(button)));
}
/*
*/
VALUE CeguiSystem_injectMouseButtonUp(VALUE self,VALUE button)
{
	return wrap(_self->injectMouseButtonUp(wrap<CEGUI::MouseButton>(button)));
}
/*
*/
VALUE CeguiSystem_injectKeyDown(VALUE self,VALUE button)
{
	return wrap(_self->injectKeyDown(NUM2UINT(button)));
}
/*
*/
VALUE CeguiSystem_injectKeyUp(VALUE self,VALUE button)
{
	return wrap(_self->injectKeyUp(NUM2UINT(button)));
}
/*
*/
VALUE CeguiSystem_injectChar(VALUE self,VALUE button)
{
	return wrap(_self->injectKeyUp(NUM2ULONG(button)));
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

void ruby_bootstrap()
{
	CEGUI::String str = CEGUI::WindowManager::EventWindowDestroyed;
	CEGUI::WindowManager::getSingletonPtr()->subscribeEvent(str,CEGUI::Event::Subscriber(ruby_window_destroyed_callback));
}
/*

*/
VALUE CeguiSystem_methodmissing(int argc,VALUE *argv,VALUE self)
{
	VALUE methId,args;
	rb_scan_args(argc, argv, "1*",&methId,&args);
	//TODO add check if system is created
	return rb_funcall2(vSystem,SYM2ID(methId),argc-1,RARRAY_PTR(args));
}
/*
*/
VALUE CeguiSystem_new(int argc,VALUE *argv,VALUE self)
{
	VALUE renderer;
	rb_scan_args(argc, argv, "10",&renderer);
	try {
		CEGUI::System::create(*wrap<CEGUI::Renderer*>(renderer));
		VALUE result = rb_funcall(self,rb_intern("allocate"),0);
		rb_funcall2(result,rb_intern("initialize"),argc,argv);
		return result;
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}


/*
*/
void Init_CeguiSystem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_define_attr(rb_cCeguiSystem,"guiSheet",1,1);
	rb_define_attr(rb_cCeguiSystem,"modalTarget",1,1);
	rb_define_attr(rb_cCeguiSystem,"defaultTooltip",1,1);
	rb_define_attr(rb_cCeguiSystem,"defaultFont",1,1);
	rb_define_attr(rb_cCeguiSystem,"xmlparser",1,1);
	rb_define_attr(rb_cCeguiSystem,"imagecodec",1,1);
#endif

	rb_cCeguiSystem = rb_define_class_under(rb_mCegui,"System",rb_cObject);
	//rb_undef_alloc_func(rb_cCeguiSystem);
	rb_define_singleton_method(rb_cCeguiSystem,"resourceProvider",RUBY_METHOD_FUNC(CeguiSystem_getResourceProvider),0);

	rb_include_module(rb_cCeguiSystem,rb_mCeguiEventSet);

	rb_define_attr_method(rb_cCeguiSystem,"guiSheet",CeguiSystem_getGUISheet,CeguiSystem_setGUISheet);
	rb_define_attr_method(rb_cCeguiSystem,"modalTarget",CeguiSystem_getModalTarget,CeguiSystem_setModalTarget);
	rb_define_attr_method(rb_cCeguiSystem,"defaultTooltip",
		CeguiSystem_getDefaultTooltip,CeguiSystem_setDefaultTooltip);
	rb_define_attr_method(rb_cCeguiSystem,"defaultFont",CeguiSystem_getDefaultFont,CeguiSystem_setDefaultFont);
	rb_define_attr_method(rb_cCeguiSystem,"defaultMouseCursor",
		CeguiSystem_getDefaultMouseCursor,CeguiSystem_setDefaultMouseCursor);
	rb_define_attr_method(rb_cCeguiSystem,"xmlparser",CeguiSystem_getXMLParser,CeguiSystem_setXMLParser);

	rb_define_attr_method(rb_cCeguiSystem,"imagecodec",CeguiSystem_getImageCodec,CeguiSystem_setImageCodec);


	rb_define_method(rb_cCeguiSystem,"renderGUI",RUBY_METHOD_FUNC(CeguiSystem_renderGUI),0);
	rb_define_method(rb_cCeguiSystem,"signalRedraw",RUBY_METHOD_FUNC(CeguiSystem_signalRedraw),0);
	rb_define_method(rb_cCeguiSystem,"redrawRequested?",RUBY_METHOD_FUNC(CeguiSystem_isRedrawRequested),0);
	
	rb_define_method(rb_cCeguiSystem,"injectMousePosition",RUBY_METHOD_FUNC(CeguiSystem_injectMousePosition),2);
	rb_define_method(rb_cCeguiSystem,"injectMouseMove",RUBY_METHOD_FUNC(CeguiSystem_injectMouseMove),2);

	rb_define_method(rb_cCeguiSystem,"injectMouseButtonDown",RUBY_METHOD_FUNC(CeguiSystem_injectMouseButtonDown),1);
	rb_define_method(rb_cCeguiSystem,"injectMouseButtonUp",RUBY_METHOD_FUNC(CeguiSystem_injectMouseButtonUp),1);

	rb_define_method(rb_cCeguiSystem,"injectKeyDown",RUBY_METHOD_FUNC(CeguiSystem_injectKeyDown),1);
	rb_define_method(rb_cCeguiSystem,"injectKeyUp",RUBY_METHOD_FUNC(CeguiSystem_injectKeyUp),1);
	rb_define_method(rb_cCeguiSystem,"injectChar",RUBY_METHOD_FUNC(CeguiSystem_injectChar),1);

	rb_define_singleton_method(rb_cCeguiSystem,"new",RUBY_METHOD_FUNC(CeguiSystem_new),-1);
	
	rb_define_singleton_method(rb_cCeguiSystem,"method_missing",RUBY_METHOD_FUNC(CeguiSystem_methodmissing),-1);
	
	rb_define_singleton_method(rb_cCeguiSystem,"defaultxmlparser",
		RUBY_METHOD_FUNC(CeguiSystem_getDefaultXMLParserName),0);
	rb_define_singleton_method(rb_cCeguiSystem,"defaultxmlparser=",
		RUBY_METHOD_FUNC(CeguiSystem_setDefaultXMLParserName),1);
	
	rb_define_singleton_method(rb_cCeguiSystem,"defaultimagecodec",
		RUBY_METHOD_FUNC(CeguiSystem_getDefaultImageCodecName),0);
	rb_define_singleton_method(rb_cCeguiSystem,"defaultimagecodec=",
		RUBY_METHOD_FUNC(CeguiSystem_setDefaultImageCodecName),1);
	
}
