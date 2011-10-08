#include "ceguiwindow.hpp"
#include "ceguilistboxitem.hpp"
#define _self wrap<CEGUI::Combobox*>(self)
VALUE rb_cCeguiCombobox;

macro_attr(Combobox,ValidationString,CEGUI::String)
macro_attr_with_func(Combobox,CaretIndex,UINT2NUM,NUM2UINT)

/*
*/
VALUE CeguiCombobox_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Combobox::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

VALUE CeguiCombobox_isReadOnly(VALUE self)
{
	return RBOOL(_self->isReadOnly());
}

VALUE CeguiCombobox_setReadOnly(VALUE self,VALUE val)
{
	_self->setReadOnly(RTEST(val));
	return val;
}



/*
*/
VALUE CeguiCombobox_isTextValid(VALUE self)
{
	return RBOOL(_self->isTextValid());
}
/*
*/
VALUE CeguiCombobox_hasInputFocus(VALUE self)
{
	return RBOOL(_self->hasInputFocus());
}


VALUE CeguiCombobox_getSelection(VALUE self)
{
	return rb_range_new(UINT2NUM(_self->getSelectionStartIndex()),UINT2NUM(_self->getSelectionEndIndex()),0);
}

VALUE CeguiCombobox_setSelection(VALUE self,VALUE val)
{
	VALUE b= rb_funcall(val,rb_intern("begin"),0);
	VALUE e= rb_funcall(val,rb_intern("end"),0);
	_self->setSelection(NUM2UINT(b),NUM2UINT(e));
	return val;
}


/*
*/
VALUE CeguiCombobox_addItem(VALUE self,VALUE item)
{
	_self->addItem(wrap<CEGUI::ListboxItem*>(item));
	return self;
}
/*
*/
VALUE CeguiCombobox_insertItem(VALUE self,VALUE pos,VALUE item)
{
	if(rb_obj_is_kind_of(pos, rb_cCeguiListboxItem)){
		_self->insertItem(wrap<CEGUI::ListboxItem*>(pos),wrap<CEGUI::ListboxItem*>(item));
	}else
		_self->insertItem(_self->getListboxItemFromIndex(NUM2UINT(pos)),wrap<CEGUI::ListboxItem*>(item));
	return self;
}
/*
*/
VALUE CeguiCombobox_removeItem(VALUE self,VALUE item)
{
	_self->removeItem(wrap<CEGUI::ListboxItem*>(item));
	return self;
}


/*
*/
VALUE CeguiCombobox_each_item(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getItemCount(); ++i)
	{
		rb_yield(wrap(_self->getListboxItemFromIndex(i)));
	}
	return self;
}
/*
*/
VALUE CeguiCombobox_selected(VALUE self)
{
	return wrap(_self->getSelectedItem());
}

/*
*/
VALUE CeguiCombobox_reset(VALUE self)
{
	_self->resetList();
	return Qnil;
}

/*
*/
VALUE CeguiCombobox_getEditbox(VALUE self)
{
	return wrap(_self->getEditbox());
}
/*
*/
VALUE CeguiCombobox_getPushButton(VALUE self)
{
	return wrap(_self->getPushButton());
}
/*
*/
VALUE CeguiCombobox_getDropList(VALUE self)
{
	return wrap(_self->getDropList());
}
/*
*/
void Init_CeguiCombobox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiCombobox,"validationString",1,1);
	rb_define_attr(rb_cCeguiCombobox,"maskCodePoint",1,1);
	
	rb_define_attr(rb_cCeguiCombobox,"caret",1,1);
	rb_define_attr(rb_cCeguiCombobox,"selection",1,1);

	rb_define_attr(rb_cCeguiCombobox,"readOnly",1,1);
	rb_define_attr(rb_cCeguiCombobox,"textMasked",1,1);

#endif

	rb_cCeguiCombobox = rb_define_class_under(rb_mCegui,"Combobox",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiCombobox,"new",RUBY_METHOD_FUNC(CeguiCombobox_new),-1);

	rb_define_attr_method(rb_cCeguiCombobox,"validationString",CeguiCombobox_getValidationString,CeguiCombobox_setValidationString);
	rb_define_attr_method(rb_cCeguiCombobox,"caret",CeguiCombobox_getCaretIndex,CeguiCombobox_setCaretIndex);
	rb_define_attr_method(rb_cCeguiCombobox,"selection",CeguiCombobox_getSelection,CeguiCombobox_setSelection);
	
	rb_define_attr_method(rb_cCeguiCombobox,"readOnly",CeguiCombobox_isReadOnly,CeguiCombobox_setReadOnly);

	rb_define_method(rb_cCeguiWindow,"text_valid?",RUBY_METHOD_FUNC(CeguiCombobox_isTextValid),0);
	rb_define_method(rb_cCeguiWindow,"inputfocus?",RUBY_METHOD_FUNC(CeguiCombobox_hasInputFocus),0);


	rb_define_method(rb_cCeguiCombobox,"addItem",RUBY_METHOD_FUNC(CeguiCombobox_addItem),1);
	rb_define_method(rb_cCeguiCombobox,"insertItem",RUBY_METHOD_FUNC(CeguiCombobox_insertItem),2);
	rb_define_method(rb_cCeguiCombobox,"removeItem",RUBY_METHOD_FUNC(CeguiCombobox_removeItem),1);
	
	rb_define_method(rb_cCeguiCombobox,"reset",RUBY_METHOD_FUNC(CeguiCombobox_reset),0);
	
	rb_define_method(rb_cCeguiCombobox,"each_item",RUBY_METHOD_FUNC(CeguiCombobox_each_item),0);
	rb_define_method(rb_cCeguiCombobox,"selected",RUBY_METHOD_FUNC(CeguiCombobox_selected),0);
	
	rb_define_method(rb_cCeguiCombobox,"editbox",RUBY_METHOD_FUNC(CeguiCombobox_getEditbox),0);
	rb_define_method(rb_cCeguiCombobox,"pushButton",RUBY_METHOD_FUNC(CeguiCombobox_getPushButton),0);
	rb_define_method(rb_cCeguiCombobox,"dropList",RUBY_METHOD_FUNC(CeguiCombobox_getDropList),0);

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
