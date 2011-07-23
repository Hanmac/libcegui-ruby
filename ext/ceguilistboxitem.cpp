#include "ceguilistboxitem.hpp"

#include "ceguiimage.hpp"
#include "ceguiwindow.hpp"
#include "ceguicolorrect.hpp"
#define _self wrap<CEGUI::ListboxItem*>(self)
VALUE rb_cCeguiListboxItem;

macro_attr(ListboxItem,Text,CEGUI::String)

macro_attr(ListboxItem,TooltipText,CEGUI::String)

macro_attr(ListboxItem,OwnerWindow,CEGUI::Window*)

macro_attr_with_func(ListboxItem,ID,UINT2NUM,NUM2UINT)

macro_attr(ListboxItem,SelectionColours,CEGUI::ColourRect)
macro_attr(ListboxItem,SelectionBrushImage,CEGUI::Image*)


/*
*/
VALUE CeguiListboxItem_getSelected(VALUE self)
{
	return RBOOL(_self->isSelected());
}
/*
*/
VALUE CeguiListboxItem_setSelected(VALUE self,VALUE val)
{
	_self->setSelected(RTEST(val));
	return val;
}
/*
*/
VALUE CeguiListboxItem_getDisabled(VALUE self)
{
	return RBOOL(_self->isDisabled());
}
/*
*/
VALUE CeguiListboxItem_setDisabled(VALUE self,VALUE val)
{
	_self->setDisabled(RTEST(val));
	return val;
}
/*
*/
VALUE CeguiListboxItem_getAutoDeleted(VALUE self)
{
	return RBOOL(_self->isAutoDeleted());
}
/*
*/
VALUE CeguiListboxItem_setAutoDeleted(VALUE self,VALUE val)
{
	_self->setAutoDeleted(RTEST(val));
	return val;
}


/*
*/
VALUE CeguiListboxItem_single_getDefaultSelectionColour(VALUE self)
{
	return wrap(CEGUI::ListboxItem::DefaultSelectionColour);
}
/*
*/
VALUE CeguiListboxItem_single_setDefaultSelectionColour(VALUE self,VALUE value)
{
	const_cast<CEGUI::colour*>(&CEGUI::ListboxItem::DefaultSelectionColour)->setRGB(wrap<CEGUI::colour>(value));
	return value;
}

/*
*/
VALUE CeguiListboxItem_draw(VALUE self,VALUE buffer,VALUE targetRect,VALUE alpha,VALUE clipper)
{
	CEGUI::GeometryBuffer *temp = wrap<CEGUI::GeometryBuffer*>(buffer);
	_self->draw(*temp,wrap<CEGUI::Rect>(targetRect),NUM2DBL(alpha),wrap<CEGUI::Rect*>(clipper));
	return self;
}
/*
*/

/*
*/
VALUE CeguiListboxItem_compare(VALUE self,VALUE other)
{
	if (rb_obj_is_kind_of(other, rb_cCeguiListboxItem)){
		return INT2NUM((*_self) > *wrap<CEGUI::ListboxItem*>(other) ? 1 :(*_self) < *wrap<CEGUI::ListboxItem*>(other) ? -1 : 0);
	}else
		return Qnil;
}

/*
 * Document-class: CEGUI::ListboxItem
 * 
 * This class represents an Listbox Item.
*/
void Init_CeguiListboxItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiListboxItem,"text",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"tooltipText",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"ownerWindow",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"id",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"selectionColors",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"selectionBrushImage",1,1);
	
	rb_define_attr(rb_cCeguiListboxItem,"selected",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"disabled",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"autodeleted",1,1);
#endif
	rb_cCeguiListboxItem = rb_define_class_under(rb_mCegui,"ListboxItem",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiListboxItem);

	rb_define_attr_method(rb_cCeguiListboxItem,"text",CeguiListboxItem_getText,CeguiListboxItem_setText);
	rb_define_attr_method(rb_cCeguiListboxItem,"tooltipText",CeguiListboxItem_getTooltipText,CeguiListboxItem_setTooltipText);
	rb_define_attr_method(rb_cCeguiListboxItem,"ownerWindow",CeguiListboxItem_getOwnerWindow,CeguiListboxItem_setOwnerWindow);
	rb_define_attr_method(rb_cCeguiListboxItem,"id",CeguiListboxItem_getID,CeguiListboxItem_setID);
	rb_define_attr_method(rb_cCeguiListboxItem,"selectionColors",CeguiListboxItem_getSelectionColours,CeguiListboxItem_setSelectionColours);
	rb_define_attr_method(rb_cCeguiListboxItem,"selectionBrushImage",CeguiListboxItem_getSelectionBrushImage,CeguiListboxItem_setSelectionBrushImage);

	rb_define_attr_method(rb_cCeguiListboxItem,"selected",CeguiListboxItem_getSelected,CeguiListboxItem_setSelected);
	rb_define_attr_method(rb_cCeguiListboxItem,"disabled",CeguiListboxItem_getDisabled,CeguiListboxItem_setDisabled);
	rb_define_attr_method(rb_cCeguiListboxItem,"autodeleted",CeguiListboxItem_getAutoDeleted,CeguiListboxItem_setAutoDeleted);

	rb_define_method(rb_cCeguiListboxItem,"<=>",RUBY_METHOD_FUNC(CeguiListboxItem_compare),1);
	rb_include_module(rb_cCeguiListboxItem,rb_mComparable);
	
	rb_define_singleton_method(rb_cCeguiListboxItem,"defaultSelectionColor",RUBY_METHOD_FUNC(CeguiListboxItem_single_getDefaultSelectionColour),0);
	rb_define_singleton_method(rb_cCeguiListboxItem,"defaultSelectionColor=",RUBY_METHOD_FUNC(CeguiListboxItem_single_setDefaultSelectionColour),1);
}
