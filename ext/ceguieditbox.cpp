#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Editbox*>(self)
VALUE rb_cCeguiEditbox;

namespace CeguiEditbox {

macro_attr(ValidationString,CEGUI::String)
macro_attr_with_func(CaretIndex,UINT2NUM,NUM2UINT)

macro_attr_with_func(MaskCodePoint,ULONG2NUM,NUM2ULONG)

macro_attr_bool(ReadOnly)
macro_attr_bool(TextMasked)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Editbox::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
VALUE _isTextValid(VALUE self)
{
	return RBOOL(_self->isTextValid());
}
/*
*/
VALUE _hasInputFocus(VALUE self)
{
	return RBOOL(_self->hasInputFocus());
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
/*
*/
void Init_CeguiEditbox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiEditbox,"validationString",1,1);
	rb_define_attr(rb_cCeguiEditbox,"maskCodePoint",1,1);
	
	rb_define_attr(rb_cCeguiEditbox,"caret",1,1);
	rb_define_attr(rb_cCeguiEditbox,"selection",1,1);

	rb_define_attr(rb_cCeguiEditbox,"readOnly",1,1);
	rb_define_attr(rb_cCeguiEditbox,"textMasked",1,1);

#endif
	using namespace CeguiEditbox;

	rb_cCeguiEditbox = rb_define_class_under(rb_mCegui,"Editbox",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiEditbox,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_attr_method(rb_cCeguiEditbox,"validationString",_getValidationString,_setValidationString);
	rb_define_attr_method(rb_cCeguiEditbox,"maskCodePoint",_getMaskCodePoint,_setMaskCodePoint);
	rb_define_attr_method(rb_cCeguiEditbox,"caret",_getCaretIndex,_setCaretIndex);
	rb_define_attr_method(rb_cCeguiEditbox,"selection",_getSelection,_setSelection);
	
	rb_define_attr_method(rb_cCeguiEditbox,"readOnly",_getReadOnly,_setReadOnly);
	rb_define_attr_method(rb_cCeguiEditbox,"textMasked",_getTextMasked,_setTextMasked);

	rb_define_method(rb_cCeguiEditbox,"text_valid?",RUBY_METHOD_FUNC(_isTextValid),0);
	rb_define_method(rb_cCeguiEditbox,"inputfocus?",RUBY_METHOD_FUNC(_hasInputFocus),0);


	rb_define_const(rb_cCeguiEditbox,"EventNamespace",wrap(CEGUI::Editbox::EventNamespace));
	rb_define_const(rb_cCeguiEditbox,"WidgetTypeName",wrap(CEGUI::Editbox::WidgetTypeName));	

	rb_define_const(rb_cCeguiEditbox,"EventReadOnlyModeChanged",wrap(CEGUI::Editbox::EventReadOnlyModeChanged));
	rb_define_const(rb_cCeguiEditbox,"EventMaskedRenderingModeChanged",wrap(CEGUI::Editbox::EventMaskedRenderingModeChanged));
	rb_define_const(rb_cCeguiEditbox,"EventMaskCodePointChanged",wrap(CEGUI::Editbox::EventMaskCodePointChanged));
	rb_define_const(rb_cCeguiEditbox,"EventValidationStringChanged",wrap(CEGUI::Editbox::EventValidationStringChanged));
	rb_define_const(rb_cCeguiEditbox,"EventMaximumTextLengthChanged",wrap(CEGUI::Editbox::EventMaximumTextLengthChanged));
	rb_define_const(rb_cCeguiEditbox,"EventTextInvalidated",wrap(CEGUI::Editbox::EventTextInvalidated));
	rb_define_const(rb_cCeguiEditbox,"EventInvalidEntryAttempted",wrap(CEGUI::Editbox::EventInvalidEntryAttempted));
	rb_define_const(rb_cCeguiEditbox,"EventCaretMoved",wrap(CEGUI::Editbox::EventCaretMoved));
	rb_define_const(rb_cCeguiEditbox,"EventTextSelectionChanged",wrap(CEGUI::Editbox::EventTextSelectionChanged));
	rb_define_const(rb_cCeguiEditbox,"EventEditboxFull",wrap(CEGUI::Editbox::EventEditboxFull));
	rb_define_const(rb_cCeguiEditbox,"EventTextAccepted",wrap(CEGUI::Editbox::EventTextAccepted));


}
