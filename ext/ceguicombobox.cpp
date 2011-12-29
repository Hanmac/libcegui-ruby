#include "ceguiwindow.hpp"
#include "ceguilistboxitem.hpp"
#define _self wrap<CEGUI::Combobox*>(self)
VALUE rb_cCeguiCombobox;

namespace CeguiCombobox {
macro_attr(ValidationString,CEGUI::String)
macro_attr(CaretIndex,uint)

macro_attr_bool(ReadOnly)

singlefunc(resetList)
singlefunc(isTextValid)
singlefunc(hasInputFocus)

singlefunc(getSelectedItem)
singlefunc(getEditbox)
singlefunc(getPushButton)
singlefunc(getDropList)

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::Combobox::WidgetTypeName);
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


/*
*/
VALUE _addItem(VALUE self,VALUE item)
{
	_self->addItem(wrap<CEGUI::ListboxItem*>(item));
	return self;
}
/*
*/
VALUE _insertItem(VALUE self,VALUE pos,VALUE item)
{
	if(rb_obj_is_kind_of(pos, rb_cCeguiListboxItem)){
		_self->insertItem(wrap<CEGUI::ListboxItem*>(pos),wrap<CEGUI::ListboxItem*>(item));
	}else
		_self->insertItem(_self->getListboxItemFromIndex(NUM2UINT(pos)),wrap<CEGUI::ListboxItem*>(item));
	return self;
}
/*
*/
VALUE _removeItem(VALUE self,VALUE item)
{
	_self->removeItem(wrap<CEGUI::ListboxItem*>(item));
	return self;
}


/*
*/
VALUE _each_item(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getItemCount(); ++i)
	{
		rb_yield(wrap(_self->getListboxItemFromIndex(i)));
	}
	return self;
}


}

/* Document-method: text_valid?
*/
/* Document-method: inputfocus?
*/
/* Document-method: clear
*/
/* Document-method: selected
*/
/* Document-method: editbox
*/
/* Document-method: pushButton
*/
/* Document-method: dropList
*/

/*
*/
void Init_CeguiCombobox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiCombobox,"validationString",1,1);
	rb_define_attr(rb_cCeguiCombobox,"maskCodePoint",1,1);
	
	rb_define_attr(rb_cCeguiCombobox,"caret",1,1);
	rb_define_attr(rb_cCeguiCombobox,"selection",1,1);

	rb_define_attr(rb_cCeguiCombobox,"readOnly",1,1);
	rb_define_attr(rb_cCeguiCombobox,"textMasked",1,1);

#endif
	using namespace CeguiCombobox;

	rb_cCeguiCombobox = rb_define_class_under(rb_mCegui,"Combobox",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiCombobox,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_attr_method(rb_cCeguiCombobox,"validationString",_getValidationString, _setValidationString);
	rb_define_attr_method(rb_cCeguiCombobox,"caret",_getCaretIndex,_setCaretIndex);
	rb_define_attr_method(rb_cCeguiCombobox,"selection",_getSelection,_setSelection);
	
	rb_define_attr_method(rb_cCeguiCombobox,"readOnly",_getReadOnly,_setReadOnly);

	rb_define_method(rb_cCeguiCombobox,"text_valid?",RUBY_METHOD_FUNC(_isTextValid),0);
	rb_define_method(rb_cCeguiCombobox,"inputfocus?",RUBY_METHOD_FUNC(_hasInputFocus),0);


	rb_define_method(rb_cCeguiCombobox,"addItem",RUBY_METHOD_FUNC(_addItem),1);
	rb_define_method(rb_cCeguiCombobox,"insertItem",RUBY_METHOD_FUNC(_insertItem),2);
	rb_define_method(rb_cCeguiCombobox,"removeItem",RUBY_METHOD_FUNC(_removeItem),1);
	
	rb_define_method(rb_cCeguiCombobox,"clear",RUBY_METHOD_FUNC(_resetList),0);
	
	rb_define_method(rb_cCeguiCombobox,"each_item",RUBY_METHOD_FUNC(_each_item),0);
	rb_define_method(rb_cCeguiCombobox,"selected",RUBY_METHOD_FUNC(_getSelectedItem),0);
	
	rb_define_method(rb_cCeguiCombobox,"editbox",RUBY_METHOD_FUNC(_getEditbox),0);
	rb_define_method(rb_cCeguiCombobox,"pushButton",RUBY_METHOD_FUNC(_getPushButton),0);
	rb_define_method(rb_cCeguiCombobox,"dropList",RUBY_METHOD_FUNC(_getDropList),0);

	rb_define_const(rb_cCeguiCombobox,"EventNamespace",wrap(CEGUI::Combobox::EventNamespace));
	rb_define_const(rb_cCeguiCombobox,"WidgetTypeName",wrap(CEGUI::Combobox::WidgetTypeName));	

	rb_define_const(rb_cCeguiCombobox,"EventReadOnlyModeChanged",wrap(CEGUI::Combobox::EventReadOnlyModeChanged));
	rb_define_const(rb_cCeguiCombobox,"EventValidationStringChanged",wrap(CEGUI::Combobox::EventValidationStringChanged));
	rb_define_const(rb_cCeguiCombobox,"EventMaximumTextLengthChanged",wrap(CEGUI::Combobox::EventMaximumTextLengthChanged));
	rb_define_const(rb_cCeguiCombobox,"EventTextInvalidated",wrap(CEGUI::Combobox::EventTextInvalidated));
	rb_define_const(rb_cCeguiCombobox,"EventInvalidEntryAttempted",wrap(CEGUI::Combobox::EventInvalidEntryAttempted));
	rb_define_const(rb_cCeguiCombobox,"EventCaretMoved",wrap(CEGUI::Combobox::EventCaretMoved));
	rb_define_const(rb_cCeguiCombobox,"EventTextSelectionChanged",wrap(CEGUI::Combobox::EventTextSelectionChanged));
	rb_define_const(rb_cCeguiCombobox,"EventEditboxFull",wrap(CEGUI::Combobox::EventEditboxFull));
	rb_define_const(rb_cCeguiCombobox,"EventTextAccepted",wrap(CEGUI::Combobox::EventTextAccepted));


}
