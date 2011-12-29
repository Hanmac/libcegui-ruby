#include "ceguielement.hpp"

#include "ceguipropertyset.hpp"
#include "ceguieventset.hpp"

#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Element*>(self)

VALUE rb_cCeguiElement;

namespace CeguiElement {

macro_attr(Height,CEGUI::UDim)
macro_attr(Width,CEGUI::UDim)
macro_attr(Area,CEGUI::URect)
macro_attr(Position,CEGUI::UVector2)
macro_attr(XPosition,CEGUI::UDim)
macro_attr(YPosition,CEGUI::UDim)

macro_attr(Size,CEGUI::USize)
macro_attr(MinSize,CEGUI::USize)
macro_attr(MaxSize,CEGUI::USize)

macro_attr(HorizontalAlignment,CEGUI::HorizontalAlignment)
macro_attr(VerticalAlignment,CEGUI::VerticalAlignment)

macro_attr(Rotation,CEGUI::Quaternion)

macro_attr(AspectRatio,float)
macro_attr_bool(PixelAligned)
macro_attr_bool(NonClient)

/*
 * call-seq:
 *   each {|element| } -> self
 *   each -> Enumerator
 * 
 * interates the child Elements
 * ===Return value
 * self
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (size_t i = 0; i < _self->getChildCount(); ++i)
		rb_yield(wrap(_self->getChildElementAtIdx(i)));
	return self;
}


VALUE _getParent(VALUE self)
{
	return wrap(_self->getParentElement());
}
VALUE _setParent(VALUE self,VALUE val)
{
	wrap<CEGUI::Element*>(val)->addChild(_self);
	return val;
}

/*
*/
VALUE _isChild(VALUE self,VALUE val)
{
	return wrap(_self->isChild(wrap<CEGUI::Element*>(val)));
}
/*
*/
VALUE _isAncestor(VALUE self,VALUE val)
{
	return wrap(_self->isAncestor(wrap<CEGUI::Element*>(val)));
}


/*
*/
VALUE _addChild(VALUE self,VALUE obj)
{
	_self->addChild(wrap<CEGUI::Element*>(obj));
	return self;
}
/*
*/
VALUE _removeChild(VALUE self,VALUE obj)
{
	_self->removeChild(wrap<CEGUI::Element*>(obj));
	return self;
}

}

/*
*/
void Init_CeguiElement(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_mCeguiPropertySet = rb_define_module_under(rb_mCegui,"PropertySet");
	rb_mCeguiEventSet = rb_define_module_under(rb_mCegui,"EventSet");

	rb_define_attr(rb_cCeguiElement,"rotation",1,1);


	rb_define_attr(rb_cCeguiElement,"area",1,1);
	rb_define_attr(rb_cCeguiElement,"height",1,1);
	rb_define_attr(rb_cCeguiElement,"width",1,1);

	rb_define_attr(rb_cCeguiElement,"position",1,1);
	rb_define_attr(rb_cCeguiElement,"xPosition",1,1);
	rb_define_attr(rb_cCeguiElement,"yPosition",1,1);

	rb_define_attr(rb_cCeguiElement,"size",1,1);
	rb_define_attr(rb_cCeguiElement,"minsize",1,1);
	rb_define_attr(rb_cCeguiElement,"maxsize",1,1);

	rb_define_attr(rb_cCeguiElement,"horizontalAlignment",1,1);
	rb_define_attr(rb_cCeguiElement,"verticalAlignment",1,1);

	rb_define_attr(rb_cCeguiElement,"parent",1,1);

	rb_define_attr(rb_cCeguiElement,"aspectRatio",1,1);
	rb_define_attr(rb_cCeguiElement,"pixelAligned",1,1);
	rb_define_attr(rb_cCeguiElement,"nonClient",1,1);
#endif

	using namespace CeguiElement;
	
	rb_cCeguiElement = rb_define_class_under(rb_mCegui,"Element",rb_cObject);
	
	rb_undef_alloc_func(rb_cCeguiElement);
	rb_include_module(rb_cCeguiElement,rb_mCeguiEventSet);
	rb_include_module(rb_cCeguiElement,rb_mCeguiPropertySet);
	
	rb_include_module(rb_cCeguiElement,rb_mEnumerable);

	rb_define_attr_method(rb_cCeguiElement,"area",_getArea,_setArea);
	rb_define_attr_method(rb_cCeguiElement,"height",_getHeight,_setHeight);
	rb_define_attr_method(rb_cCeguiElement,"width",_getWidth,_setWidth);
	
	rb_define_attr_method(rb_cCeguiElement,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cCeguiElement,"xPosition",_getXPosition,_setXPosition);
	rb_define_attr_method(rb_cCeguiElement,"yPosition",_getYPosition,_setYPosition);


	rb_define_attr_method(rb_cCeguiElement,"size",_getSize,_setSize);
	rb_define_attr_method(rb_cCeguiElement,"minsize",_getMinSize,_setMinSize);
	rb_define_attr_method(rb_cCeguiElement,"maxsize",_getMaxSize,_setMaxSize);

	rb_define_attr_method(rb_cCeguiElement,"horizontalAlignment",_getHorizontalAlignment,_setHorizontalAlignment);
	rb_define_attr_method(rb_cCeguiElement,"verticalAlignment",_getVerticalAlignment,_setVerticalAlignment);

	rb_define_attr_method(rb_cCeguiElement,"parent",_getParent,_setParent);

	rb_define_attr_method(rb_cCeguiElement,"rotation",_getRotation,_setRotation);

	rb_define_attr_method(rb_cCeguiElement,"aspectRatio",_getAspectRatio,_setAspectRatio);
	rb_define_attr_method(rb_cCeguiElement,"pixelAligned",_getPixelAligned,_setPixelAligned);
	rb_define_attr_method(rb_cCeguiElement,"rotation",_getNonClient,_setNonClient);

	rb_define_method(rb_cCeguiElement,"each",RUBY_METHOD_FUNC(_each),0);

	rb_define_method(rb_cCeguiElement,"isChild?",RUBY_METHOD_FUNC(_isChild),1);
	rb_define_method(rb_cCeguiElement,"isAncestor?",RUBY_METHOD_FUNC(_isAncestor),1);

	rb_define_method(rb_cCeguiElement,"addChild",RUBY_METHOD_FUNC(_addChild),1);
	rb_define_method(rb_cCeguiElement,"removeChild",RUBY_METHOD_FUNC(_removeChild),1);

	rb_define_const(rb_cCeguiElement,"EventNamespace",wrap(CEGUI::Element::EventNamespace));
	rb_define_const(rb_cCeguiElement,"EventSized",wrap(CEGUI::Element::EventSized));
	rb_define_const(rb_cCeguiElement,"EventParentSized",wrap(CEGUI::Element::EventParentSized));
	rb_define_const(rb_cCeguiElement,"EventMoved",wrap(CEGUI::Element::EventMoved));
	rb_define_const(rb_cCeguiElement,"EventHorizontalAlignmentChanged",wrap(CEGUI::Element::EventHorizontalAlignmentChanged));
	rb_define_const(rb_cCeguiElement,"EventVerticalAlignmentChanged",wrap(CEGUI::Element::EventVerticalAlignmentChanged));
	rb_define_const(rb_cCeguiElement,"EventRotated",wrap(CEGUI::Element::EventRotated));
	rb_define_const(rb_cCeguiElement,"EventChildAdded",wrap(CEGUI::Element::EventChildAdded));
	rb_define_const(rb_cCeguiElement,"EventChildRemoved",wrap(CEGUI::Element::EventChildRemoved));
	rb_define_const(rb_cCeguiElement,"EventZOrderChanged",wrap(CEGUI::Element::EventZOrderChanged));
	rb_define_const(rb_cCeguiElement,"EventNonClientChanged",wrap(CEGUI::Element::EventNonClientChanged));
}
