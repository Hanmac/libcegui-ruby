#include "ceguiwindow.hpp"

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

#define _self wrap<CEGUI::Window*>(self)
#define _manager CEGUI::WindowManager::getSingletonPtr()
#define _factorymanager CEGUI::WindowFactoryManager::getSingletonPtr()
VALUE rb_cCeguiWindow;
std::map<CEGUI::Window*,RubyWindowHolder*> rubywindowholder;
VALUE rb_windowholder;
macro_attr(Window,Rotation,CEGUI::Quaternion)
macro_attr(Window,Text,CEGUI::String)

macro_attr(Window,Tooltip,CEGUI::Tooltip*)
macro_attr(Window,TooltipType,CEGUI::String)
macro_attr(Window,TooltipText,CEGUI::String)

macro_attr(Window,LookNFeel,CEGUI::String)


macro_attr(Window,Height,CEGUI::UDim)
macro_attr(Window,Width,CEGUI::UDim)
macro_attr(Window,Area,CEGUI::URect)
macro_attr(Window,Position,CEGUI::UVector2)
macro_attr(Window,XPosition,CEGUI::UDim)
macro_attr(Window,YPosition,CEGUI::UDim)

macro_attr(Window,Size,CEGUI::USize)
macro_attr(Window,MinSize,CEGUI::USize)
macro_attr(Window,MaxSize,CEGUI::USize)

macro_attr(Window,Margin,CEGUI::UBox)



macro_attr(Window,Alpha,float)

VALUE CeguiWindow_getName(VALUE self)
{
	return wrap(_self->getName());
}
VALUE CeguiWindow_setName(VALUE self,VALUE val)
{
	_self->rename(wrap<CEGUI::String>(val));
	return val;
}


VALUE CeguiWindow_getParent(VALUE self)
{
	return wrap(_self->getParent());
}
VALUE CeguiWindow_setParent(VALUE self,VALUE val)
{
	wrap<CEGUI::Window*>(val)->addChild(_self);
	return val;
}
/*
*/
VALUE CeguiWindow_getType(VALUE self)
{
	return wrap(_self->getType());
}


/*
*/
VALUE CeguiWindow_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (size_t i = 0; i < _self->getChildCount(); ++i)
		rb_yield(wrap(_self->getChildAtIdx(i)));
	return self;
}
/*
*/
VALUE CeguiWindow_get(VALUE self,VALUE name)
{
	return wrap(_self->getChild(wrap<CEGUI::String>(name)));
}



/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiWindow_inspect(VALUE self)
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
				array[2]=CeguiWindow_getName(self);
				return rb_f_sprintf(3,array);
			}
		VALUE array[4];
		array[0]=rb_str_new2("#<%s(%s):%s>");
		array[1]=rb_class_of(self);
		array[2]=CeguiWindow_getType(self);
		array[3]=CeguiWindow_getName(self);
		return rb_f_sprintf(4,array);
	}
}

/*
*/
VALUE CeguiWindow_render(VALUE self)
{
	_self->render();
	return Qnil;
}
/*
*/
VALUE CeguiWindow_destroy(VALUE self)
{
	_self->destroy();
	return Qnil;
}
/*
*/
VALUE CeguiWindow_captureInput(VALUE self)
{
	return RBOOL(_self->captureInput());
}
/*
*/
VALUE CeguiWindow_releaseInput(VALUE self)
{
	_self->releaseInput();
	return Qnil;
}
/*
*/
VALUE CeguiWindow_beginInitialisation(VALUE self)
{
	_self->beginInitialisation();
	return Qnil;
}
/*
*/
VALUE CeguiWindow_endInitialisation(VALUE self)
{
	_self->endInitialisation();
	return Qnil;
}

/*
*/
VALUE CeguiWindow_isChild(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cString)){
		return RBOOL(_self->isChild(wrap<CEGUI::String>(val)));
	}else if(rb_obj_is_kind_of(val, rb_cInteger)){
		return RBOOL(_self->isChild(NUM2ULONG(val)));
	}else
		return RBOOL(_self->isChild(wrap<CEGUI::Window*>(val)));
}
/*
*/
VALUE CeguiWindow_isAncestor(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cString)){
		return RBOOL(_self->isAncestor(wrap<CEGUI::String>(val)));
	}else if(rb_obj_is_kind_of(val, rb_cInteger)){
		return RBOOL(_self->isAncestor(NUM2ULONG(val)));
	}else
		return RBOOL(_self->isAncestor(wrap<CEGUI::Window*>(val)));
}
/*
*/
VALUE CeguiWindow_getActiveChild(VALUE self)
{
	return wrap(_self->getActiveChild());
}
/*
*/
VALUE CeguiWindow_getActiveSibling(VALUE self)
{
	return wrap(_self->getActiveSibling());
}
/*
*/
VALUE CeguiWindow_getRootWindow(VALUE self)
{
	return wrap(_self->getRootWindow());
}
/*
*/
VALUE CeguiWindow_getPixelSize(VALUE self)
{
	return wrap(_self->getPixelSize());
}

/*
*/
VALUE CeguiWindow_writeXML(VALUE self,VALUE xml)
{
	CEGUI::XMLSerializer *temp =wrap<CEGUI::XMLSerializer*>(xml);
	_self->writeXMLToStream(*temp);
	return self;
}
/*
*/
VALUE CeguiWindow_saveLayout(VALUE self,VALUE obj)
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
VALUE CeguiWindow_Manager_new(int argc,VALUE *argv,VALUE self)
{
	VALUE type,name;
	rb_scan_args(argc, argv, "11",&type,&name);
	try {
		VALUE result = wrap(_manager->createWindow(wrap<CEGUI::String>(type),wrap<CEGUI::String>(name)));
		rb_funcall2(result,rb_intern("initialize"),argc,argv);
		return result;
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}
/*
*/
VALUE CeguiWindow_Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_manager->getIterator());
	return self;
}
/*
*/
VALUE CeguiWindow_Manager_lock(VALUE self)
{
	_manager->lock();
	return RBOOL(_manager->isLocked());
}
/*
*/
VALUE CeguiWindow_Manager_unlock(VALUE self)
{
	_manager->unlock();
	return RBOOL(_manager->isLocked());
}
/*
*/
VALUE CeguiWindow_Manager_locked(VALUE self)
{
	return RBOOL(_manager->isLocked());
}





bool 	windowcallback(CEGUI::Window *window, CEGUI::String &propname, CEGUI::String &propvalue, void *userdata){
	return RTEST(rb_funcall((VALUE)userdata,rb_intern("call"),3,wrap(window),wrap(propname),wrap(propvalue)));
}

/*
*/
VALUE CeguiWindow_Manager_loadLayout(int argc,VALUE *argv,VALUE self)
{
	VALUE filename,resourceGroup;
	rb_scan_args(argc, argv, "11",&filename,&resourceGroup);
	try{
		if(rb_block_given_p()){
			return wrap(_manager->loadLayoutFromFile(wrap<CEGUI::String>(filename),wrap<CEGUI::String>(resourceGroup),windowcallback,(void*)rb_block_proc()));
		}else
			return wrap(_manager->loadLayoutFromFile(wrap<CEGUI::String>(filename),wrap<CEGUI::String>(resourceGroup)));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}

/*
*/
VALUE CeguiWindow_Manager_each_type(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_factorymanager->getIterator());
	return self;
}
/*
*/
VALUE CeguiWindow_Manager_each_alias(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_factorymanager->getAliasIterator());
	return self;
}
/*
*/
VALUE CeguiWindow_Manager_each_falagard(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_factorymanager->getFalagardMappingIterator());
	return self;
}


/*
*/
VALUE CeguiWindow_Manager_destroyAllWindows(VALUE self)
{
	_manager->destroyAllWindows();
	return self;
}
/*
*/
VALUE CeguiWindow_Manager_cleanDeadPool(VALUE self)
{
	_manager->cleanDeadPool();
	return self;
}

/*
*/
VALUE CeguiWindow_Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::WindowManager::getDefaultResourceGroup());
}
/*
*/
VALUE CeguiWindow_Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::WindowManager::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}


int ruby_window_destroyed_callback(const CEGUI::EventArgs &arg)
{
	const CEGUI::WindowEventArgs *wea=dynamic_cast<const CEGUI::WindowEventArgs*>(&arg);
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(wea->window);
	if(it!=rubywindowholder.end())
	{
		it->second->window = NULL;
		rb_ary_delete(rb_windowholder,it->second->ruby);
	}
	return 0;
}

void Init_CeguiWindow(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_define_attr(rb_cCeguiWindow,"rotation",1,1);
	rb_define_attr(rb_cCeguiWindow,"text",1,1);
	rb_define_attr(rb_cCeguiWindow,"name",1,1);

	rb_define_attr(rb_cCeguiWindow,"parent",1,1);

	rb_define_attr(rb_cCeguiWindow,"area",1,1);
	rb_define_attr(rb_cCeguiWindow,"height",1,1);
	rb_define_attr(rb_cCeguiWindow,"width",1,1);
	
	rb_define_attr(rb_cCeguiWindow,"lookNFeel",1,1);
	
	rb_define_attr(rb_cCeguiWindow,"position",1,1);
	
	rb_define_attr(rb_cCeguiWindow,"xPosition",1,1);
	rb_define_attr(rb_cCeguiWindow,"yPosition",1,1);

	rb_define_attr(rb_cCeguiWindow,"size",1,1);
	rb_define_attr(rb_cCeguiWindow,"minsize",1,1);
	rb_define_attr(rb_cCeguiWindow,"maxsize",1,1);
	
	rb_define_attr(rb_cCeguiWindow,"margin",1,1);
	
	rb_define_attr(rb_cCeguiWindow,"tooltip",1,1);
	rb_define_attr(rb_cCeguiWindow,"tooltipType",1,1);
	rb_define_attr(rb_cCeguiWindow,"tooltipText",1,1);
#endif
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiWindow);
	rb_include_module(rb_cCeguiWindow,rb_mCeguiEventSet);
	rb_include_module(rb_cCeguiWindow,rb_mCeguiPropertySet);
	
	rb_include_module(rb_cCeguiWindow,rb_mEnumerable);

	rb_extend_object(rb_cCeguiWindow,rb_mCeguiEventSet);
	rb_extend_object(rb_cCeguiWindow,rb_mEnumerable);
	
	rb_define_attr_method(rb_cCeguiWindow,"rotation",CeguiWindow_getRotation,CeguiWindow_setRotation);
	rb_define_attr_method(rb_cCeguiWindow,"text",CeguiWindow_getText,CeguiWindow_setText);
	rb_define_attr_method(rb_cCeguiWindow,"name",CeguiWindow_getName,CeguiWindow_setName);
	
	rb_define_attr_method(rb_cCeguiWindow,"parent",CeguiWindow_getParent,CeguiWindow_setParent);
	
	rb_define_attr_method(rb_cCeguiWindow,"area",CeguiWindow_getArea,CeguiWindow_setArea);
	rb_define_attr_method(rb_cCeguiWindow,"height",CeguiWindow_getHeight,CeguiWindow_setHeight);
	rb_define_attr_method(rb_cCeguiWindow,"width",CeguiWindow_getWidth,CeguiWindow_setWidth);
	
	rb_define_attr_method(rb_cCeguiWindow,"position",CeguiWindow_getPosition,CeguiWindow_setPosition);
	rb_define_attr_method(rb_cCeguiWindow,"xPosition",CeguiWindow_getXPosition,CeguiWindow_setXPosition);
	rb_define_attr_method(rb_cCeguiWindow,"yPosition",CeguiWindow_getYPosition,CeguiWindow_setYPosition);	

	rb_define_attr_method(rb_cCeguiWindow,"size",CeguiWindow_getSize,CeguiWindow_setSize);
	rb_define_attr_method(rb_cCeguiWindow,"minsize",CeguiWindow_getMinSize,CeguiWindow_setMinSize);
	rb_define_attr_method(rb_cCeguiWindow,"maxsize",CeguiWindow_getMaxSize,CeguiWindow_setMaxSize);

	rb_define_attr_method(rb_cCeguiWindow,"margin",CeguiWindow_getMargin,CeguiWindow_setMargin);

	rb_define_attr_method(rb_cCeguiWindow,"lookNFeel",CeguiWindow_getLookNFeel,CeguiWindow_setLookNFeel);

	rb_define_attr_method(rb_cCeguiWindow,"alpha",CeguiWindow_getAlpha,CeguiWindow_setAlpha);

	rb_define_attr_method(rb_cCeguiWindow,"tooltip",CeguiWindow_getTooltip,CeguiWindow_setTooltip);
	rb_define_attr_method(rb_cCeguiWindow,"tooltipType",CeguiWindow_getTooltipType,CeguiWindow_setTooltipType);
	rb_define_attr_method(rb_cCeguiWindow,"tooltipText",CeguiWindow_getTooltipText,CeguiWindow_setTooltipText);

	rb_define_method(rb_cCeguiWindow,"type",RUBY_METHOD_FUNC(CeguiWindow_getType),0);

	rb_define_method(rb_cCeguiWindow,"render",RUBY_METHOD_FUNC(CeguiWindow_render),0);
	rb_define_method(rb_cCeguiWindow,"destroy",RUBY_METHOD_FUNC(CeguiWindow_destroy),0);

	rb_define_method(rb_cCeguiWindow,"saveLayout",RUBY_METHOD_FUNC(CeguiWindow_saveLayout),-1);

	rb_define_method(rb_cCeguiWindow,"captureInput",RUBY_METHOD_FUNC(CeguiWindow_captureInput),0);
	rb_define_method(rb_cCeguiWindow,"releaseInput",RUBY_METHOD_FUNC(CeguiWindow_releaseInput),0);

	rb_define_method(rb_cCeguiWindow,"beginInitialisation",RUBY_METHOD_FUNC(CeguiWindow_beginInitialisation),0);
	rb_define_method(rb_cCeguiWindow,"endInitialisation",RUBY_METHOD_FUNC(CeguiWindow_endInitialisation),0);

	rb_define_method(rb_cCeguiWindow,"[]",RUBY_METHOD_FUNC(CeguiWindow_get),1);

	rb_define_method(rb_cCeguiWindow,"child?",RUBY_METHOD_FUNC(CeguiWindow_isChild),1);
	rb_define_method(rb_cCeguiWindow,"ancestor?",RUBY_METHOD_FUNC(CeguiWindow_isAncestor),1);


	rb_define_method(rb_cCeguiWindow,"activeChild",RUBY_METHOD_FUNC(CeguiWindow_getActiveChild),0);
	rb_define_method(rb_cCeguiWindow,"activeSibling",RUBY_METHOD_FUNC(CeguiWindow_getActiveSibling),0);
	rb_define_method(rb_cCeguiWindow,"rootWindow",RUBY_METHOD_FUNC(CeguiWindow_getRootWindow),0);

	rb_define_method(rb_cCeguiWindow,"pixelSize",RUBY_METHOD_FUNC(CeguiWindow_getPixelSize),0);


	rb_define_method(rb_cCeguiWindow,"each",RUBY_METHOD_FUNC(CeguiWindow_each),0);	

	rb_define_method(rb_cCeguiWindow,"inspect",RUBY_METHOD_FUNC(CeguiWindow_inspect),0);

	rb_define_method(rb_cCeguiWindow,"writeXML",RUBY_METHOD_FUNC(CeguiWindow_writeXML),1);

	rb_define_singleton_method(rb_cCeguiWindow,"new",RUBY_METHOD_FUNC(CeguiWindow_Manager_new),-1);

	rb_define_singleton_method(rb_cCeguiWindow,"loadLayout",RUBY_METHOD_FUNC(CeguiWindow_Manager_loadLayout),-1);

	rb_define_singleton_method(rb_cCeguiWindow,"each",RUBY_METHOD_FUNC(CeguiWindow_Manager_each),0);
	rb_define_singleton_method(rb_cCeguiWindow,"each_type",RUBY_METHOD_FUNC(CeguiWindow_Manager_each_type),0);
	rb_define_singleton_method(rb_cCeguiWindow,"each_alias",RUBY_METHOD_FUNC(CeguiWindow_Manager_each_alias),0);
	rb_define_singleton_method(rb_cCeguiWindow,"each_falagard",RUBY_METHOD_FUNC(CeguiWindow_Manager_each_falagard),0);


	rb_define_singleton_method(rb_cCeguiWindow,"lock",RUBY_METHOD_FUNC(CeguiWindow_Manager_lock),0);
	rb_define_singleton_method(rb_cCeguiWindow,"unlock",RUBY_METHOD_FUNC(CeguiWindow_Manager_unlock),0);
	rb_define_singleton_method(rb_cCeguiWindow,"locked?",RUBY_METHOD_FUNC(CeguiWindow_Manager_locked),0);

	rb_define_singleton_method(rb_cCeguiWindow,"cleanDeadPool",RUBY_METHOD_FUNC(CeguiWindow_Manager_cleanDeadPool),0);

	rb_define_singleton_method(rb_cCeguiWindow,"destroyAllWindows",RUBY_METHOD_FUNC(CeguiWindow_Manager_destroyAllWindows),0);


	rb_define_singleton_method(rb_cCeguiWindow,"defaultResourceGroup",RUBY_METHOD_FUNC(CeguiWindow_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiWindow,"defaultResourceGroup=",RUBY_METHOD_FUNC(CeguiWindow_Manager_setDefaultResourceGroup),1);

	rb_define_const(rb_cCeguiWindow,"EventUpdated",wrap(CEGUI::Window::EventUpdated));
	rb_define_const(rb_cCeguiWindow,"EventParentSized",wrap(CEGUI::Window::EventParentSized));
	rb_define_const(rb_cCeguiWindow,"EventSized",wrap(CEGUI::Window::EventSized));
	rb_define_const(rb_cCeguiWindow,"EventMoved",wrap(CEGUI::Window::EventMoved));
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
	rb_define_const(rb_cCeguiWindow,"EventChildAdded",wrap(CEGUI::Window::EventChildAdded));
	rb_define_const(rb_cCeguiWindow,"EventChildRemoved",wrap(CEGUI::Window::EventChildRemoved));
	rb_define_const(rb_cCeguiWindow,"EventDestructionStarted",wrap(CEGUI::Window::EventDestructionStarted));
	rb_define_const(rb_cCeguiWindow,"EventZOrderChanged",wrap(CEGUI::Window::EventZOrderChanged));
	rb_define_const(rb_cCeguiWindow,"EventDragDropItemEnters",wrap(CEGUI::Window::EventDragDropItemEnters));
	rb_define_const(rb_cCeguiWindow,"EventDragDropItemLeaves",wrap(CEGUI::Window::EventDragDropItemLeaves));
	rb_define_const(rb_cCeguiWindow,"EventDragDropItemDropped",wrap(CEGUI::Window::EventDragDropItemDropped));
	rb_define_const(rb_cCeguiWindow,"EventVerticalAlignmentChanged",wrap(CEGUI::Window::EventVerticalAlignmentChanged));
	rb_define_const(rb_cCeguiWindow,"EventHorizontalAlignmentChanged",wrap(CEGUI::Window::EventHorizontalAlignmentChanged));
	rb_define_const(rb_cCeguiWindow,"EventWindowRendererAttached",wrap(CEGUI::Window::EventWindowRendererAttached));
	rb_define_const(rb_cCeguiWindow,"EventWindowRendererDetached",wrap(CEGUI::Window::EventWindowRendererDetached));
	rb_define_const(rb_cCeguiWindow,"EventRotated",wrap(CEGUI::Window::EventRotated));
	rb_define_const(rb_cCeguiWindow,"EventNonClientChanged",wrap(CEGUI::Window::EventNonClientChanged));
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

	rb_windowholder = rb_ary_new();
	rb_global_variable(&rb_windowholder);
}
