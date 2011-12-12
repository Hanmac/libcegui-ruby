/*
 * ceguisequentiallayoutcontainer.cpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::SequentialLayoutContainer*>(self)
VALUE rb_cCeguiSequentialLayoutContainer;

namespace CeguiSequentialLayoutContainer {



VALUE _getPositionOfChild(VALUE self,VALUE obj)
{
	if(rb_obj_is_kind_of(obj, rb_cCeguiWindow)) {
		CEGUI::Window* wnd = wrap<CEGUI::Window*>(obj);
		if(_self->isChild(wnd)){
			return UINT2NUM(_self->getPositionOfChild(wnd));
		}
	}else if(rb_obj_is_kind_of(obj, rb_cString)) {
		CEGUI::String name = wrap<CEGUI::String>(obj);
		if(_self->isChild(name)){
			return UINT2NUM(_self->getPositionOfChild(name));
		}
	}
	return Qnil;
}

VALUE _swapChildren(VALUE self,VALUE obj1,VALUE obj2)
{
	size_t id1,id2;
	CEGUI::Window *cobj1, *cobj2;
	if(rb_obj_is_kind_of(obj1, rb_cCeguiWindow)) {
		cobj1 = wrap<CEGUI::Window*>(obj1);
	}else if(rb_obj_is_kind_of(obj1, rb_cString)) {
		cobj1 = _self->getChild(wrap<CEGUI::String>(obj1));
	}else if(rb_obj_is_kind_of(obj1, rb_cInteger)) {

	}else
		return self;
	if(rb_obj_is_kind_of(obj1, rb_cInteger)) {
		id1 = NUM2UINT(obj1);
	}else
		id1 = _self->getPositionOfChild(cobj1);

	if(rb_obj_is_kind_of(obj2, rb_cCeguiWindow)) {
		cobj2 = wrap<CEGUI::Window*>(obj2);
	}else if(rb_obj_is_kind_of(obj1, rb_cString)) {
		cobj2 = _self->getChild(wrap<CEGUI::String>(obj2));
	}else if(rb_obj_is_kind_of(obj2, rb_cInteger)) {

	}else
		return self;
	if(rb_obj_is_kind_of(obj2, rb_cInteger)) {
		id2 = NUM2UINT(obj2);
	}else
		id2 = _self->getPositionOfChild(cobj2);

	_self->swapChildPositions(id1,id2);
	return self;
}

VALUE _moveChildTo(VALUE self,VALUE obj,VALUE position)
{
	if(rb_obj_is_kind_of(obj, rb_cCeguiWindow)) {
		_self->moveChildToPosition(wrap<CEGUI::Window*>(obj),NUM2UINT(position));
	}else if(rb_obj_is_kind_of(obj, rb_cString)) {
		_self->moveChildToPosition(wrap<CEGUI::String>(obj),NUM2UINT(position));
	}
	return self;
}
}

/*
*/
void Init_CeguiSequentialLayoutContainer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiLayoutContainer = rb_define_class_under(rb_mCegui,"LayoutContainer",rb_cCeguiWindow);
#endif
	using namespace CeguiSequentialLayoutContainer;

	rb_cCeguiSequentialLayoutContainer = rb_define_class_under(rb_mCegui,"SequentialLayoutContainer",rb_cCeguiLayoutContainer);

	rb_define_method(rb_cCeguiSequentialLayoutContainer,"swapChildren",RUBY_METHOD_FUNC(_swapChildren),2);
	rb_define_method(rb_cCeguiSequentialLayoutContainer,"moveChildTo",RUBY_METHOD_FUNC(_moveChildTo),2);

	rb_define_method(rb_cCeguiSequentialLayoutContainer,"positionOfChild",RUBY_METHOD_FUNC(_getPositionOfChild),1);


	rb_define_const(rb_cCeguiSequentialLayoutContainer,"EventNamespace",wrap(CEGUI::SequentialLayoutContainer::EventNamespace));

	rb_define_const(rb_cCeguiSequentialLayoutContainer,"EventChildOrderChanged",wrap(CEGUI::SequentialLayoutContainer::EventChildOrderChanged));
}
