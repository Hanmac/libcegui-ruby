#include "ceguielement.hpp"

#include "ceguitooltip.hpp"

#include "ceguisize.hpp"
#include "ceguivector3.hpp"

#include "ceguiudim.hpp"
#include "ceguiuvector2.hpp"
#include "ceguiubox.hpp"

#include "ceguipropertyset.hpp"
#include "ceguieventset.hpp"

#include "ceguifalagard.hpp"
#include "ceguiexception.hpp"

#include "ceguiostream.hpp"
#include "ceguiquaternion.hpp"

#define _self wrap<CEGUI::Window*>(self)
#define _manager CEGUI::WindowManager::getSingletonPtr()
#define _factorymanager CEGUI::WindowFactoryManager::getSingletonPtr()
VALUE rb_cCeguiWindow;
std::map<CEGUI::Window*,RubyWindowHolder*> rubywindowholder;
VALUE rb_windowholder;


RubyWindowHolder::RubyWindowHolder(CEGUI::Window *window,VALUE klass) :
		window(window), ruby(Data_Wrap_Struct(klass, NULL, free, this))
{
	rb_hash_aset(rb_windowholder,INT2NUM(this->ruby),this->ruby);
	rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(window,this));
}

VALUE RubyWindowHolder::get(CEGUI::Window *window,VALUE klass)
{
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(window);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder(window,klass);
		return hold->ruby;
	}
}

namespace CeguiWindow
{

macro_attr(ID,uint)

macro_attr(Text,CEGUI::String)

macro_attr(Tooltip,CEGUI::Tooltip*)
macro_attr(TooltipType,CEGUI::String)
macro_attr(TooltipText,CEGUI::String)

macro_attr(LookNFeel,CEGUI::String)

macro_attr(Margin,CEGUI::UBox)

macro_attr(Alpha,float)
macro_attr(AutoRepeatDelay,float)
macro_attr(AutoRepeatRate,float)

macro_attr_bool(Disabled)
macro_attr_bool(Visible)

macro_attr_bool(DragDropTarget)
macro_attr_bool(ClippedByParent)
macro_attr_bool(MouseAutoRepeatEnabled)
macro_attr_bool(ZOrderingEnabled)

macro_attr(MouseCursor,CEGUI::Image*)

macro_attr(UpdateMode,CEGUI::WindowUpdateMode)

singlefunc(render)
singlefunc(destroy)

singlefunc(releaseInput)
singlereturn(captureInput)

singlefunc(beginInitialisation)
singlefunc(endInitialisation)

singlefunc(show)
singlefunc(hide)

singlefunc(enable)
singlefunc(disable)

singlefunc(activate)
singlefunc(deactivate)

singlereturn(getType)

singlereturn(getActiveChild)
singlereturn(getActiveSibling)

singlereturn(getRootWindow)
singlereturn(getPixelSize)

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	if(wrap< RubyWindowHolder* >(self)->window==NULL){
		VALUE array[2];
		array[0]=rb_str_new2("#<%s:(destroyed)>");
		array[1]=rb_class_of(self);
		return rb_f_sprintf(2,array);
	}else{
		if(rb_const_defined(rb_class_of(self),rb_intern("WidgetTypeName")))
			if(_self->getType() == wrap<CEGUI::String>(rb_const_get(rb_class_of(self),rb_intern("WidgetTypeName"))))
			{
				VALUE array[3];
				array[0]=rb_str_new2("#<%s:%s>");
				array[1]=rb_class_of(self);
				array[2]=rb_funcall(self,rb_intern("name"),0);
				return rb_f_sprintf(3,array);
			}
		VALUE array[4];
		array[0]=rb_str_new2("#<%s(%s):%s>");
		array[1]=rb_class_of(self);
		array[2]=_getType(self);
		array[3]=rb_funcall(self,rb_intern("name"),0);
		return rb_f_sprintf(4,array);
	}
}
/*
*/
VALUE _isChild(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cInteger)){
		return wrap(_self->isChild(NUM2ULONG(val)));
	}else
		return rb_call_super(1,&val);
}
/*
*/
VALUE _isAncestor(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cInteger)){
		return wrap(_self->isAncestor(NUM2ULONG(val)));
	}else
		return rb_call_super(1,&val);
}

/*
*/
VALUE _writeXML(VALUE self,VALUE xml)
{
	CEGUI::XMLSerializer *temp =wrap<CEGUI::XMLSerializer*>(xml);
	_self->writeXMLToStream(*temp);
	return self;
}
/*
*/
VALUE _saveLayout(VALUE self,VALUE obj)
{
	if(rb_obj_is_kind_of(obj, rb_cString)){
		_manager->saveLayoutToFile(*_self,wrap<CEGUI::String>(obj));
	}else{
		std::ostream *os = new std::ostream(new RubyStreamBuf(obj));
		_manager->writeLayoutToStream(*_self,*os);
	}
	return self;
}
/*
*/
VALUE _addChild(int argc,VALUE *argv,VALUE self)
{
	VALUE type,name;
	rb_scan_args(argc, argv, "11",&type,&name);
	if(rb_obj_is_kind_of(type, rb_cCeguiElement)){
		rb_call_super(argc,argv);
		return self;
	}else{
		try {
			VALUE result = wrap(_manager->createWindow(wrap<CEGUI::String>(type),wrap<CEGUI::String>(name)));
			rb_funcall2(result,rb_intern("initialize"),argc,argv);
			if(rb_block_given_p())
				rb_yield(result);
			_self->addChild(wrap<CEGUI::Window*>(result));
			return result;
		}catch(CEGUI::Exception& e){
			rb_raise(e);
			return Qnil;
		}
		return self;
	}
}
/*
*/
VALUE _removeChild(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cInteger)){
		_self->removeChild(NUM2ULONG(val));
	}else
		return rb_call_super(1,&val);
	return self;

}
/*
*/
VALUE _Manager_new(int argc,VALUE *argv,VALUE self)
{
	//check if system is created
	wrap< CEGUI::System* >(self);
	VALUE type,name;
	rb_scan_args(argc, argv, "11",&type,&name);
	try {
		VALUE result = wrap(_manager->createWindow(wrap<CEGUI::String>(type),wrap<CEGUI::String>(name)));
		rb_funcall2(result,rb_intern("initialize"),argc,argv);
		return result;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	//check if system is created
	wrap< CEGUI::System* >(self);
	wrap_each(_manager->getIterator());
	return self;
}
/*
*/
VALUE _Manager_lock(VALUE self)
{
	//check if system is created
	wrap< CEGUI::System* >(self);
	_manager->lock();
	return wrap(_manager->isLocked());
}
/*
*/
VALUE _Manager_unlock(VALUE self)
{
	//check if system is created
	wrap< CEGUI::System* >(self);
	_manager->unlock();
	return wrap(_manager->isLocked());
}
/*
*/
VALUE _Manager_locked(VALUE self)
{
	//check if system is created
	wrap< CEGUI::System* >(self);
	return wrap(_manager->isLocked());
}





bool windowcallback(CEGUI::Window *window, CEGUI::String &propname, CEGUI::String &propvalue, void *userdata){
	return RTEST(rb_funcall((VALUE)userdata,rb_intern("call"),3,wrap(window),wrap(propname),wrap(propvalue)));
}

/*
*/
VALUE _Manager_loadLayout(int argc,VALUE *argv,VALUE self)
{
	//check if system is created
	wrap< CEGUI::System* >(self);
	
	VALUE filename,resourceGroup;
	rb_scan_args(argc, argv, "11",&filename,&resourceGroup);
	try{
		if(rb_block_given_p()){
			return wrap(_manager->loadLayoutFromFile(wrap<CEGUI::String>(filename),wrap<CEGUI::String>(resourceGroup),windowcallback,(void*)rb_block_proc()));
		}else
			return wrap(_manager->loadLayoutFromFile(wrap<CEGUI::String>(filename),wrap<CEGUI::String>(resourceGroup)));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _Manager_loadLayoutString(VALUE self,VALUE string)
{
	//check if system is created
	wrap< CEGUI::System* >(self);

	try{
		if(rb_block_given_p()){
			return wrap(_manager->loadLayoutFromString(wrap<CEGUI::String>(string),windowcallback,(void*)rb_block_proc()));
		}else
			return wrap(_manager->loadLayoutFromString(wrap<CEGUI::String>(string)));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}

/*
*/
VALUE _Manager_each_type(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	//check if system is created
	wrap< CEGUI::System* >(self);
	wrap_each(_factorymanager->getIterator());
	return self;
}
/*
*/
VALUE _Manager_each_alias(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	//check if system is created
	wrap< CEGUI::System* >(self);
	wrap_each(_factorymanager->getAliasIterator());
	return self;
}
/*
*/
VALUE _Manager_each_falagard(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	//check if system is created
	wrap< CEGUI::System* >(self);
	wrap_each(_factorymanager->getFalagardMappingIterator());
	return self;
}


/*
*/
VALUE _Manager_destroyAllWindows(VALUE self)
{
	//check if system is created
	wrap< CEGUI::System* >(self);
	_manager->destroyAllWindows();
	return self;
}
/*
*/
VALUE _Manager_cleanDeadPool(VALUE self)
{
	//check if system is created
	wrap< CEGUI::System* >(self);
	_manager->cleanDeadPool();
	return self;
}

/*
*/
VALUE _Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::WindowManager::getDefaultResourceGroup());
}
/*
*/
VALUE _Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::WindowManager::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}

}

int ruby_window_destroyed_callback(const CEGUI::EventArgs &arg)
{
	const CEGUI::WindowEventArgs *wea=dynamic_cast<const CEGUI::WindowEventArgs*>(&arg);
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(wea->window);
	if(it!=rubywindowholder.end())
	{
		it->second->window = NULL;
		rb_hash_delete(rb_windowholder,INT2NUM(it->second->ruby));
		rubywindowholder.erase(it);
	}
	return 0;
}


/* Document-method: render
 * call-seq:
 *   render -> self
 * 
 * renders this window
 * ===Return value
 * self
*/
/* Document-method: destroy
 * call-seq:
 *   destroy -> self
 * 
 * destroy this window
 * ===Return value
 * self
*/

/* Document-method: releaseInput
*/

/* Document-method: captureInput
*/

/* Document-method: beginInitialisation
*/
/* Document-method: endInitialisation
*/

/* Document-method: show
*/
/* Document-method: hide
*/

/* Document-method: enable
*/
/* Document-method: disable
*/

/* Document-method: activate
*/
/* Document-method: deactivate
*/

/* Document-method: type
 * call-seq:
 *   type
 *
 * returns the type of the window
 * ===Return value
 * string
*/

/* Document-method: activeChild
*/
/* Document-method: activeSibling
*/
/* Document-method: pixelSize
*/


/* Document-method: rootWindow
 * call-seq:
 *   rootWindow -> CEGUI::Window
 *
 * gets the root window of this window
 * ===Return value
 * CEGUI::Window or nil
*/

void Init_CeguiWindow(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiWindow,"id",1,1);

	rb_define_attr(rb_cCeguiWindow,"text",1,1);

	rb_define_attr(rb_cCeguiWindow,"lookNFeel",1,1);
	rb_define_attr(rb_cCeguiWindow,"alpha",1,1);

	rb_define_attr(rb_cCeguiWindow,"margin",1,1);
	
	rb_define_attr(rb_cCeguiWindow,"tooltip",1,1);
	rb_define_attr(rb_cCeguiWindow,"tooltipType",1,1);
	rb_define_attr(rb_cCeguiWindow,"tooltipText",1,1);

	rb_define_attr(rb_cCeguiWindow,"autoRepeatDelay",1,1);
	rb_define_attr(rb_cCeguiWindow,"autoRepeatRate",1,1);

	rb_define_attr(rb_cCeguiWindow,"dragDropTarget",1,1);
	rb_define_attr(rb_cCeguiWindow,"clippedByParent",1,1);
	rb_define_attr(rb_cCeguiWindow,"mouseAutoRepeatEnabled",1,1);
	rb_define_attr(rb_cCeguiWindow,"zOrderingEnabled",1,1);

	rb_define_attr(rb_cCeguiWindow,"mouseCursor",1,1);
	
	rb_define_attr(rb_cCeguiWindow,"updateMode",1,1);

	rb_cCeguiElement = rb_define_class_under(rb_mCegui,"Element",rb_cObject);
	rb_cCeguiNamedElement = rb_define_class_under(rb_mCegui,"NamedElement",rb_cCeguiElement);
#endif

	using namespace CeguiWindow;

	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cCeguiNamedElement);
	rb_undef_alloc_func(rb_cCeguiWindow);

	rb_define_method(rb_cCeguiWindow,"initialize",RUBY_METHOD_FUNC(Cegui_dummy2),2);


	rb_extend_object(rb_cCeguiWindow,rb_mCeguiEventSet);
	rb_extend_object(rb_cCeguiWindow,rb_mEnumerable);
	
	rb_define_attr_method(rb_cCeguiWindow,"id",_getID,_setID);

	rb_define_attr_method(rb_cCeguiWindow,"text",_getText,_setText);

	rb_define_attr_method(rb_cCeguiWindow,"margin",_getMargin,_setMargin);

	rb_define_attr_method(rb_cCeguiWindow,"lookNFeel",_getLookNFeel,_setLookNFeel);

	rb_define_attr_method(rb_cCeguiWindow,"alpha",_getAlpha,_setAlpha);

	rb_define_attr_method(rb_cCeguiWindow,"tooltip",_getTooltip,_setTooltip);
	rb_define_attr_method(rb_cCeguiWindow,"tooltipType",_getTooltipType,_setTooltipType);
	rb_define_attr_method(rb_cCeguiWindow,"tooltipText",_getTooltipText,_setTooltipText);

	rb_define_attr_method(rb_cCeguiWindow,"autoRepeatDelay",_getAutoRepeatDelay,_setAutoRepeatDelay);
	rb_define_attr_method(rb_cCeguiWindow,"autoRepeatRate",_getAutoRepeatRate,_setAutoRepeatRate);

	rb_define_attr_method(rb_cCeguiWindow,"dragDropTarget",_getDragDropTarget,_setDragDropTarget);
	rb_define_attr_method(rb_cCeguiWindow,"clippedByParent",_getClippedByParent,_setClippedByParent);
	rb_define_attr_method(rb_cCeguiWindow,"mouseAutoRepeatEnabled",_getMouseAutoRepeatEnabled,_setMouseAutoRepeatEnabled);
	rb_define_attr_method(rb_cCeguiWindow,"zOrderingEnabled",_getZOrderingEnabled,_setZOrderingEnabled);
	rb_define_attr_method(rb_cCeguiWindow,"mouseCursor",_getMouseCursor,_setMouseCursor);

	rb_define_attr_method(rb_cCeguiWindow,"updateMode",_getUpdateMode,_setUpdateMode);


	rb_define_method(rb_cCeguiWindow,"type",RUBY_METHOD_FUNC(_getType),0);

	rb_define_method(rb_cCeguiWindow,"render",RUBY_METHOD_FUNC(_render),0);
	rb_define_method(rb_cCeguiWindow,"destroy",RUBY_METHOD_FUNC(_destroy),0);

	rb_define_method(rb_cCeguiWindow,"show",RUBY_METHOD_FUNC(_show),0);
	rb_define_method(rb_cCeguiWindow,"hide",RUBY_METHOD_FUNC(_hide),0);

	rb_define_method(rb_cCeguiWindow,"enable",RUBY_METHOD_FUNC(_enable),0);
	rb_define_method(rb_cCeguiWindow,"disable",RUBY_METHOD_FUNC(_disable),0);

	rb_define_method(rb_cCeguiWindow,"activate",RUBY_METHOD_FUNC(_activate),0);
	rb_define_method(rb_cCeguiWindow,"deactivate",RUBY_METHOD_FUNC(_deactivate),0);



	rb_define_method(rb_cCeguiWindow,"saveLayout",RUBY_METHOD_FUNC(_saveLayout),-1);

	rb_define_method(rb_cCeguiWindow,"captureInput",RUBY_METHOD_FUNC(_captureInput),0);
	rb_define_method(rb_cCeguiWindow,"releaseInput",RUBY_METHOD_FUNC(_releaseInput),0);

	rb_define_method(rb_cCeguiWindow,"beginInitialisation",RUBY_METHOD_FUNC(_beginInitialisation),0);
	rb_define_method(rb_cCeguiWindow,"endInitialisation",RUBY_METHOD_FUNC(_endInitialisation),0);

	rb_define_method(rb_cCeguiWindow,"child?",RUBY_METHOD_FUNC(_isChild),1);
	rb_define_method(rb_cCeguiWindow,"ancestor?",RUBY_METHOD_FUNC(_isAncestor),1);


	rb_define_method(rb_cCeguiWindow,"activeChild",RUBY_METHOD_FUNC(_getActiveChild),0);
	rb_define_method(rb_cCeguiWindow,"activeSibling",RUBY_METHOD_FUNC(_getActiveSibling),0);
	rb_define_method(rb_cCeguiWindow,"rootWindow",RUBY_METHOD_FUNC(_getRootWindow),0);

	rb_define_method(rb_cCeguiWindow,"pixelSize",RUBY_METHOD_FUNC(_getPixelSize),0);


	rb_define_method(rb_cCeguiWindow,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiWindow,"writeXML",RUBY_METHOD_FUNC(_writeXML),1);

	rb_define_singleton_method(rb_cCeguiWindow,"new",RUBY_METHOD_FUNC(_Manager_new),-1);

	rb_define_singleton_method(rb_cCeguiWindow,"loadLayout",RUBY_METHOD_FUNC(_Manager_loadLayout),-1);
	rb_define_singleton_method(rb_cCeguiWindow,"loadLayoutString",RUBY_METHOD_FUNC(_Manager_loadLayoutString),1);

	rb_define_singleton_method(rb_cCeguiWindow,"each",RUBY_METHOD_FUNC(_Manager_each),0);
	rb_define_singleton_method(rb_cCeguiWindow,"each_type",RUBY_METHOD_FUNC(_Manager_each_type),0);
	rb_define_singleton_method(rb_cCeguiWindow,"each_alias",RUBY_METHOD_FUNC(_Manager_each_alias),0);
	rb_define_singleton_method(rb_cCeguiWindow,"each_falagard",RUBY_METHOD_FUNC(_Manager_each_falagard),0);


	rb_define_singleton_method(rb_cCeguiWindow,"lock",RUBY_METHOD_FUNC(_Manager_lock),0);
	rb_define_singleton_method(rb_cCeguiWindow,"unlock",RUBY_METHOD_FUNC(_Manager_unlock),0);
	rb_define_singleton_method(rb_cCeguiWindow,"locked?",RUBY_METHOD_FUNC(_Manager_locked),0);

	rb_define_singleton_method(rb_cCeguiWindow,"cleanDeadPool",RUBY_METHOD_FUNC(_Manager_cleanDeadPool),0);

	rb_define_singleton_method(rb_cCeguiWindow,"destroyAllWindows",RUBY_METHOD_FUNC(_Manager_destroyAllWindows),0);


	rb_define_singleton_method(rb_cCeguiWindow,"defaultResourceGroup",RUBY_METHOD_FUNC(_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiWindow,"defaultResourceGroup=",RUBY_METHOD_FUNC(_Manager_setDefaultResourceGroup),1);

	rb_define_const(rb_cCeguiWindow,"EventUpdated",wrap(CEGUI::Window::EventUpdated));
	rb_define_const(rb_cCeguiWindow,"EventTextChanged",wrap(CEGUI::Window::EventTextChanged));
	rb_define_const(rb_cCeguiWindow,"EventFontChanged",wrap(CEGUI::Window::EventFontChanged));
	rb_define_const(rb_cCeguiWindow,"EventAlphaChanged",wrap(CEGUI::Window::EventAlphaChanged));
	rb_define_const(rb_cCeguiWindow,"EventIDChanged",wrap(CEGUI::Window::EventIDChanged));
	rb_define_const(rb_cCeguiWindow,"EventActivated",wrap(CEGUI::Window::EventActivated));
	rb_define_const(rb_cCeguiWindow,"EventDeactivated",wrap(CEGUI::Window::EventDeactivated));
	rb_define_const(rb_cCeguiWindow,"EventShown",wrap(CEGUI::Window::EventShown));
	rb_define_const(rb_cCeguiWindow,"EventHidden",wrap(CEGUI::Window::EventHidden));
	rb_define_const(rb_cCeguiWindow,"EventEnabled",wrap(CEGUI::Window::EventEnabled));
	rb_define_const(rb_cCeguiWindow,"EventDisabled",wrap(CEGUI::Window::EventDisabled));
	rb_define_const(rb_cCeguiWindow,"EventClippedByParentChanged",wrap(CEGUI::Window::EventClippedByParentChanged));
	rb_define_const(rb_cCeguiWindow,"EventDestroyedByParentChanged",wrap(CEGUI::Window::EventDestroyedByParentChanged));
	rb_define_const(rb_cCeguiWindow,"EventInheritsAlphaChanged",wrap(CEGUI::Window::EventInheritsAlphaChanged));
	rb_define_const(rb_cCeguiWindow,"EventAlwaysOnTopChanged",wrap(CEGUI::Window::EventAlwaysOnTopChanged));
	rb_define_const(rb_cCeguiWindow,"EventInputCaptureGained",wrap(CEGUI::Window::EventInputCaptureGained));
	rb_define_const(rb_cCeguiWindow,"EventInputCaptureLost",wrap(CEGUI::Window::EventInputCaptureLost));
	rb_define_const(rb_cCeguiWindow,"EventRenderingStarted",wrap(CEGUI::Window::EventRenderingStarted));
	rb_define_const(rb_cCeguiWindow,"EventRenderingEnded",wrap(CEGUI::Window::EventRenderingEnded));
	rb_define_const(rb_cCeguiWindow,"EventDestructionStarted",wrap(CEGUI::Window::EventDestructionStarted));
	rb_define_const(rb_cCeguiWindow,"EventDragDropItemEnters",wrap(CEGUI::Window::EventDragDropItemEnters));
	rb_define_const(rb_cCeguiWindow,"EventDragDropItemLeaves",wrap(CEGUI::Window::EventDragDropItemLeaves));
	rb_define_const(rb_cCeguiWindow,"EventDragDropItemDropped",wrap(CEGUI::Window::EventDragDropItemDropped));
	rb_define_const(rb_cCeguiWindow,"EventWindowRendererAttached",wrap(CEGUI::Window::EventWindowRendererAttached));
	rb_define_const(rb_cCeguiWindow,"EventWindowRendererDetached",wrap(CEGUI::Window::EventWindowRendererDetached));
	rb_define_const(rb_cCeguiWindow,"EventTextParsingChanged",wrap(CEGUI::Window::EventTextParsingChanged));
	rb_define_const(rb_cCeguiWindow,"EventMarginChanged",wrap(CEGUI::Window::EventMarginChanged));
	rb_define_const(rb_cCeguiWindow,"EventMouseEntersArea",wrap(CEGUI::Window::EventMouseEntersArea));
	rb_define_const(rb_cCeguiWindow,"EventMouseLeavesArea",wrap(CEGUI::Window::EventMouseLeavesArea));
	rb_define_const(rb_cCeguiWindow,"EventMouseEntersSurface",wrap(CEGUI::Window::EventMouseEntersSurface));
	rb_define_const(rb_cCeguiWindow,"EventMouseLeavesSurface",wrap(CEGUI::Window::EventMouseLeavesSurface));
	rb_define_const(rb_cCeguiWindow,"EventMouseMove",wrap(CEGUI::Window::EventMouseMove));
	rb_define_const(rb_cCeguiWindow,"EventMouseWheel",wrap(CEGUI::Window::EventMouseWheel));
	rb_define_const(rb_cCeguiWindow,"EventMouseButtonDown",wrap(CEGUI::Window::EventMouseButtonDown));
	rb_define_const(rb_cCeguiWindow,"EventMouseButtonUp",wrap(CEGUI::Window::EventMouseButtonUp));
	rb_define_const(rb_cCeguiWindow,"EventMouseClick",wrap(CEGUI::Window::EventMouseClick));
	rb_define_const(rb_cCeguiWindow,"EventMouseDoubleClick",wrap(CEGUI::Window::EventMouseDoubleClick));
	rb_define_const(rb_cCeguiWindow,"EventMouseTripleClick",wrap(CEGUI::Window::EventMouseTripleClick));
	rb_define_const(rb_cCeguiWindow,"EventKeyDown",wrap(CEGUI::Window::EventKeyDown));
	rb_define_const(rb_cCeguiWindow,"EventKeyUp",wrap(CEGUI::Window::EventKeyUp));
	rb_define_const(rb_cCeguiWindow,"EventCharacterKey",wrap(CEGUI::Window::EventCharacterKey));

	rb_windowholder = rb_hash_new();
	rb_global_variable(&rb_windowholder);
}
