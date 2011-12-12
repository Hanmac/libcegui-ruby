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

#include "ceguirenderedstringparser.hpp"

#define _self wrap< CEGUI::System* >(rb_mCeguiSystem)

VALUE rb_mCeguiSystem;

namespace CeguiSystem{

macro_attr(GUISheet,CEGUI::Window*)
macro_attr(ModalTarget,CEGUI::Window*)
macro_attr(ScriptingModule,CEGUI::ScriptModule*)

macro_attr(DefaultMouseCursor,CEGUI::Image*)

macro_attr(DefaultFont,CEGUI::Font*)

macro_attr(SingleClickTimeout,double)
macro_attr(MultiClickTimeout,double)
macro_attr(MultiClickToleranceAreaSize,CEGUI::Sizef)

macro_attr_bool(MouseClickEventGenerationEnabled)

macro_attr(MouseMoveScaling,float)

macro_attr(DefaultCustomRenderedStringParser,CEGUI::RenderedStringParser*)

singlefunc(signalRedraw)
singlefunc(renderGUI)

/*
*/
VALUE _getResourceProvider(VALUE self)
{
	return wrap(_self->getResourceProvider());
}
/*
*/
VALUE _getDefaultTooltip(VALUE self)
{
	return wrap(_self->getDefaultTooltip());
}
/*
*/
VALUE _setDefaultTooltip(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cString))
		_self->setDefaultTooltip(wrap<CEGUI::String>(val));
	else
		_self->setDefaultTooltip(wrap<CEGUI::Tooltip*>(val));
	return val;
}
/*
*/
VALUE _getXMLParser(VALUE self)
{
	return wrap(_self->getXMLParser());
}
/*
*/
VALUE _setXMLParser(VALUE self,VALUE val)
{
	try{
		if(rb_obj_is_kind_of(val, rb_cString))
			_self->setXMLParser(wrap<CEGUI::String>(val));
		else
			_self->setXMLParser(wrap<CEGUI::XMLParser*>(val));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return val;
}

/*
*/
VALUE _getImageCodec(VALUE self)
{
	return wrap(_self->getImageCodec());
}
/*
*/
VALUE _setImageCodec(VALUE self,VALUE val)
{
	try{
		if(rb_obj_is_kind_of(val, rb_cString))
			_self->setImageCodec(wrap<CEGUI::String>(val));
		else
			_self->setImageCodec(*wrap<CEGUI::ImageCodec*>(val));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return val;
}

/*
*/
VALUE _isRedrawRequested(VALUE self)
{
	return wrap(_self->isRedrawRequested());
}

/*
*/
VALUE _injectMousePosition(VALUE self,VALUE x,VALUE y)
{
	return wrap(_self->injectMousePosition(NUM2DBL(x),NUM2DBL(y)));
}
/*
*/
VALUE _injectMouseMove(VALUE self,VALUE x,VALUE y)
{
	return wrap(_self->injectMouseMove(NUM2DBL(x),NUM2DBL(y)));
}

/*
*/
VALUE _injectMouseButtonDown(VALUE self,VALUE button)
{
	return wrap(_self->injectMouseButtonDown(wrap<CEGUI::MouseButton>(button)));
}
/*
*/
VALUE _injectMouseButtonUp(VALUE self,VALUE button)
{
	return wrap(_self->injectMouseButtonUp(wrap<CEGUI::MouseButton>(button)));
}
/*
*/
VALUE _injectKeyDown(VALUE self,VALUE button)
{
	return wrap(_self->injectKeyDown(NUM2UINT(button)));
}
/*
*/
VALUE _injectKeyUp(VALUE self,VALUE button)
{
	return wrap(_self->injectKeyUp(NUM2UINT(button)));
}
/*
*/
VALUE _injectChar(VALUE self,VALUE button)
{
	return wrap(_self->injectKeyUp(NUM2ULONG(button)));
}

/*
*/
VALUE _setDefaultXMLParserName(VALUE self,VALUE val)
{
	CEGUI::System::setDefaultXMLParserName(wrap<CEGUI::String>(val));
 	return val;
}
/*
*/ 	
VALUE _getDefaultXMLParserName(VALUE self)
{
	return wrap(CEGUI::System::getDefaultXMLParserName());
}
/*
*/
VALUE _setDefaultImageCodecName(VALUE self,VALUE val)
{
	CEGUI::System::setDefaultImageCodecName(wrap<CEGUI::String>(val));
 	return val;
}
/*
*/
VALUE _getDefaultImageCodecName(VALUE self)
{
	return wrap(CEGUI::System::getDefaultImageCodecName());
}

/*
*/
VALUE _create(int argc,VALUE *argv,VALUE self)
{
	VALUE renderer;
	rb_scan_args(argc, argv, "10",&renderer);
	try {
		CEGUI::System::create(*wrap<CEGUI::Renderer*>(renderer));
		return self;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}

}

void ruby_bootstrap()
{
	CEGUI::String str = CEGUI::WindowManager::EventWindowDestroyed;
	CEGUI::WindowManager::getSingletonPtr()->subscribeEvent(str,CEGUI::Event::Subscriber(ruby_window_destroyed_callback));
}

/* Document-method: guiSheet 

*/
/* Document-method: modalTarget 

*/
/* Document-method: defaultMouseCursor 

*/

/* Document-method: defaultFont

*/

/* Document-method: singleClickTimeout

*/
/* Document-method: multiClickTimeout

*/
/* Document-method: multiClickToleranceAreaSize

*/

/* Document-method: mouseClickEventGenerationEnabled

*/
/* Document-method: mouseMoveScaling

*/
/* Document-method: defaultCustomRenderedStringParser

*/



/* Document-method: guiSheet=

*/
/* Document-method: modalTarget=

*/
/* Document-method: defaultMouseCursor=

*/

/* Document-method: defaultFont=

*/
/* Document-method: singleClickTimeout=

*/
/* Document-method: multiClickTimeout=

*/
/* Document-method: multiClickToleranceAreaSize=

*/


/* Document-method: mouseClickEventGenerationEnabled=

*/
/* Document-method: mouseMoveScaling=

*/
/* Document-method: defaultCustomRenderedStringParser=

*/

/* Document-method: renderGUI

*/
/* Document-method: signalRedraw

*/

/*
*/
void Init_CeguiSystem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif

	using namespace CeguiSystem;

	rb_mCeguiSystem = rb_define_class_under(rb_mCegui,"System",rb_cObject);
	rb_define_module_function(rb_mCeguiSystem,"resourceProvider",RUBY_METHOD_FUNC(_getResourceProvider),0);

	rb_extend_object(rb_mCeguiSystem,rb_mCeguiEventSet);

	rb_define_module_function(rb_mCeguiSystem,"guiSheet",RUBY_METHOD_FUNC(_getGUISheet),0);
	rb_define_module_function(rb_mCeguiSystem,"modalTarget",RUBY_METHOD_FUNC(_getModalTarget),0);
	rb_define_module_function(rb_mCeguiSystem,"defaultTooltip",RUBY_METHOD_FUNC(_getDefaultTooltip),0);
	rb_define_module_function(rb_mCeguiSystem,"defaultFont",RUBY_METHOD_FUNC(_getDefaultFont),0);
	rb_define_module_function(rb_mCeguiSystem,"defaultMouseCursor",RUBY_METHOD_FUNC(_getDefaultMouseCursor),0);
	rb_define_module_function(rb_mCeguiSystem,"xmlparser",RUBY_METHOD_FUNC(_getXMLParser),0);
	rb_define_module_function(rb_mCeguiSystem,"imagecodec",RUBY_METHOD_FUNC(_getImageCodec),0);

	rb_define_module_function(rb_mCeguiSystem,"singleClickTimeout",RUBY_METHOD_FUNC(_getSingleClickTimeout),0);
	rb_define_module_function(rb_mCeguiSystem,"multiClickTimeout",RUBY_METHOD_FUNC(_getMultiClickTimeout),0);
	rb_define_module_function(rb_mCeguiSystem,"multiClickToleranceAreaSize",RUBY_METHOD_FUNC(_getMultiClickToleranceAreaSize),0);
	rb_define_module_function(rb_mCeguiSystem,"mouseClickEventGenerationEnabled",RUBY_METHOD_FUNC(_getMouseClickEventGenerationEnabled),0);
	rb_define_module_function(rb_mCeguiSystem,"mouseMoveScaling",RUBY_METHOD_FUNC(_getMouseMoveScaling),0);
	rb_define_module_function(rb_mCeguiSystem,"defaultCustomRenderedStringParser",RUBY_METHOD_FUNC(_getDefaultCustomRenderedStringParser),0);
	
	rb_define_module_function(rb_mCeguiSystem,"guiSheet=",RUBY_METHOD_FUNC(_setGUISheet),1);
	rb_define_module_function(rb_mCeguiSystem,"modalTarget=",RUBY_METHOD_FUNC(_setModalTarget),1);
	rb_define_module_function(rb_mCeguiSystem,"defaultTooltip=",RUBY_METHOD_FUNC(_setDefaultTooltip),1);
	rb_define_module_function(rb_mCeguiSystem,"defaultFont=",RUBY_METHOD_FUNC(_setDefaultFont),1);
	rb_define_module_function(rb_mCeguiSystem,"defaultMouseCursor=",RUBY_METHOD_FUNC(_setDefaultMouseCursor),1);
	rb_define_module_function(rb_mCeguiSystem,"xmlparser=",RUBY_METHOD_FUNC(_setXMLParser),1);
	rb_define_module_function(rb_mCeguiSystem,"imagecodec=",RUBY_METHOD_FUNC(_setImageCodec),1);

	rb_define_module_function(rb_mCeguiSystem,"singleClickTimeout=",RUBY_METHOD_FUNC(_setSingleClickTimeout),1);
	rb_define_module_function(rb_mCeguiSystem,"multiClickTimeout=",RUBY_METHOD_FUNC(_setMultiClickTimeout),1);
	rb_define_module_function(rb_mCeguiSystem,"multiClickToleranceAreaSize=",RUBY_METHOD_FUNC(_setMultiClickToleranceAreaSize),1);
	rb_define_module_function(rb_mCeguiSystem,"mouseClickEventGenerationEnabled=",RUBY_METHOD_FUNC(_setMouseClickEventGenerationEnabled),1);
	rb_define_module_function(rb_mCeguiSystem,"mouseMoveScaling=",RUBY_METHOD_FUNC(_setMouseMoveScaling),1);
	rb_define_module_function(rb_mCeguiSystem,"defaultCustomRenderedStringParser=",RUBY_METHOD_FUNC(_setDefaultCustomRenderedStringParser),1);


	rb_define_module_function(rb_mCeguiSystem,"renderGUI",RUBY_METHOD_FUNC(_renderGUI),0);
	rb_define_module_function(rb_mCeguiSystem,"signalRedraw",RUBY_METHOD_FUNC(_signalRedraw),0);
	rb_define_module_function(rb_mCeguiSystem,"redrawRequested?",RUBY_METHOD_FUNC(_isRedrawRequested),0);
	
	rb_define_module_function(rb_mCeguiSystem,"injectMousePosition",RUBY_METHOD_FUNC(_injectMousePosition),2);
	rb_define_module_function(rb_mCeguiSystem,"injectMouseMove",RUBY_METHOD_FUNC(_injectMouseMove),2);

	rb_define_module_function(rb_mCeguiSystem,"injectMouseButtonDown",RUBY_METHOD_FUNC(_injectMouseButtonDown),1);
	rb_define_module_function(rb_mCeguiSystem,"injectMouseButtonUp",RUBY_METHOD_FUNC(_injectMouseButtonUp),1);

	rb_define_module_function(rb_mCeguiSystem,"injectKeyDown",RUBY_METHOD_FUNC(_injectKeyDown),1);
	rb_define_module_function(rb_mCeguiSystem,"injectKeyUp",RUBY_METHOD_FUNC(_injectKeyUp),1);
	rb_define_module_function(rb_mCeguiSystem,"injectChar",RUBY_METHOD_FUNC(_injectChar),1);

	rb_define_module_function(rb_mCeguiSystem,"create",RUBY_METHOD_FUNC(_create),-1);
	
	rb_define_module_function(rb_mCeguiSystem,"defaultxmlparser",
		RUBY_METHOD_FUNC(_getDefaultXMLParserName),0);
	rb_define_module_function(rb_mCeguiSystem,"defaultxmlparser=",
		RUBY_METHOD_FUNC(_setDefaultXMLParserName),1);
	
	rb_define_module_function(rb_mCeguiSystem,"defaultimagecodec",
		RUBY_METHOD_FUNC(_getDefaultImageCodecName),0);
	rb_define_module_function(rb_mCeguiSystem,"defaultimagecodec=",
		RUBY_METHOD_FUNC(_setDefaultImageCodecName),1);
	
}
