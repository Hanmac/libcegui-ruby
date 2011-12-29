/*
 * ceguimultilineeditbox.cpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::MultiLineEditbox*>(self)
VALUE rb_cCeguiMultiLineEditbox;

namespace CeguiMultiLineEditbox {

macro_attr(CaretIndex,uint)
macro_attr(MaxTextLength,uint)

macro_attr_bool(ReadOnly)
macro_attr(SelectionBrushImage,CEGUI::Image*)

singlereturn(hasInputFocus)

singlereturn(isWordWrapped)

singlereturn(getVertScrollbar)
singlereturn(getHorzScrollbar)


VALUE _getShowVertScrollbar(VALUE self)
{
	return wrap(_self->isVertScrollbarAlwaysShown());
}
VALUE _setShowVertScrollbar(VALUE self,VALUE val)
{
	_self->setShowVertScrollbar(wrap<bool>(val));
	return val;
}

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::MultiLineEditbox::WidgetTypeName);
	result[1]=name;
	return rb_call_super(2,result);
}


VALUE _getSelection(VALUE self)
{
	return rb_range_new(UINT2NUM(_self->getSelectionStartIndex()),UINT2NUM(_self->getSelectionEndIndex()),0);
}

VALUE _setSelection(VALUE self,VALUE val)
{
	VALUE b= rb_funcall(val,rb_intern("begin"),0);
	VALUE e= rb_funcall(val,rb_intern("end"),0);
	_self->setSelection(NUM2UINT(b),NUM2UINT(e));
	return val;
}


}

/* Document-method: text_valid?
*/
/* Document-method: inputfocus?
*/

/*
*/
void Init_CeguiMultiLineEditbox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiEditbox,"caret",1,1);
	rb_define_attr(rb_cCeguiEditbox,"selection",1,1);

	rb_define_attr(rb_cCeguiEditbox,"readOnly",1,1);

#endif
	using namespace CeguiMultiLineEditbox;

	rb_cCeguiMultiLineEditbox = rb_define_class_under(rb_mCegui,"MultiLineEditbox",rb_cCeguiWindow);

	rb_define_singleton_method(rb_cCeguiMultiLineEditbox,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_attr_method(rb_cCeguiMultiLineEditbox,"caret",_getCaretIndex,_setCaretIndex);
	rb_define_attr_method(rb_cCeguiMultiLineEditbox,"selection",_getSelection,_setSelection);

	rb_define_attr_method(rb_cCeguiMultiLineEditbox,"readOnly",_getReadOnly,_setReadOnly);

	rb_define_method(rb_cCeguiMultiLineEditbox,"inputfocus?",RUBY_METHOD_FUNC(_hasInputFocus),0);


	rb_define_const(rb_cCeguiMultiLineEditbox,"EventNamespace",wrap(CEGUI::MultiLineEditbox::EventNamespace));
	rb_define_const(rb_cCeguiMultiLineEditbox,"WidgetTypeName",wrap(CEGUI::MultiLineEditbox::WidgetTypeName));

	rb_define_const(rb_cCeguiMultiLineEditbox,"EventReadOnlyModeChanged",wrap(CEGUI::MultiLineEditbox::EventReadOnlyModeChanged));
	rb_define_const(rb_cCeguiMultiLineEditbox,"EventWordWrapModeChanged",wrap(CEGUI::MultiLineEditbox::EventWordWrapModeChanged));
	rb_define_const(rb_cCeguiMultiLineEditbox,"EventMaximumTextLengthChanged",wrap(CEGUI::MultiLineEditbox::EventMaximumTextLengthChanged));
	rb_define_const(rb_cCeguiMultiLineEditbox,"EventCaretMoved",wrap(CEGUI::MultiLineEditbox::EventCaretMoved));
	rb_define_const(rb_cCeguiMultiLineEditbox,"EventTextSelectionChanged",wrap(CEGUI::MultiLineEditbox::EventTextSelectionChanged));
	rb_define_const(rb_cCeguiMultiLineEditbox,"EventEditboxFull",wrap(CEGUI::MultiLineEditbox::EventEditboxFull));

	rb_define_const(rb_cCeguiMultiLineEditbox,"EventVertScrollbarModeChanged",wrap(CEGUI::MultiLineEditbox::EventVertScrollbarModeChanged));
	rb_define_const(rb_cCeguiMultiLineEditbox,"EventHorzScrollbarModeChanged",wrap(CEGUI::MultiLineEditbox::EventHorzScrollbarModeChanged));

	rb_define_const(rb_cCeguiMultiLineEditbox,"VertScrollbarName",wrap(CEGUI::MultiLineEditbox::VertScrollbarName));
	rb_define_const(rb_cCeguiMultiLineEditbox,"HorzScrollbarName",wrap(CEGUI::MultiLineEditbox::HorzScrollbarName));

}

