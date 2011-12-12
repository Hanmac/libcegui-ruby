#include "ceguilistboxitem.hpp"

#include "ceguiimage.hpp"
#include "ceguiwindow.hpp"
#include "ceguicolorrect.hpp"
#define _self wrap<CEGUI::ListboxItem*>(self)
VALUE rb_cCeguiListboxItem;

namespace CeguiListboxItem {
macro_attr(Text,CEGUI::String)

macro_attr(TooltipText,CEGUI::String)

macro_attr(OwnerWindow,CEGUI::Window*)

macro_attr_with_func(ID,UINT2NUM,NUM2UINT)

macro_attr(SelectionColours,CEGUI::ColourRect)
macro_attr(SelectionBrushImage,CEGUI::Image*)

macro_attr_bool(Selected)
macro_attr_bool(Disabled)
macro_attr_bool(AutoDeleted)

/*
*/
VALUE _initialize(VALUE self, VALUE text)
{
	return _setText(self,text);
}

/*
*/
VALUE _single_getDefaultSelectionColour(VALUE self)
{
	return wrap(CEGUI::ListboxItem::DefaultSelectionColour);
}
/*
*/
VALUE _single_setDefaultSelectionColour(VALUE self,VALUE value)
{
	const_cast<CEGUI::Colour*>(&CEGUI::ListboxItem::DefaultSelectionColour)->setRGB(wrap<CEGUI::Colour>(value));
	return value;
}

/*
*/
VALUE _draw(VALUE self,VALUE buffer,VALUE targetRect,VALUE alpha,VALUE clipper)
{
	CEGUI::GeometryBuffer *temp = wrap<CEGUI::GeometryBuffer*>(buffer);
	_self->draw(*temp,wrap<CEGUI::Rectf>(targetRect),NUM2DBL(alpha),wrap<CEGUI::Rectf*>(clipper));
	return self;
}
/*
*/

/*
*/
VALUE _compare(VALUE self,VALUE other)
{
	if (rb_obj_is_kind_of(other, rb_cCeguiListboxItem)){
		return INT2NUM((*_self) > *wrap<CEGUI::ListboxItem*>(other) ? 1 :(*_self) < *wrap<CEGUI::ListboxItem*>(other) ? -1 : 0);
	}else
		return Qnil;
}

}
/*
 * Document-class: CEGUI::ListboxItem
 * 
 * This class represents an Listbox Item.
*/
void Init_CeguiListboxItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
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
	
	using namespace CeguiListboxItem;

	rb_cCeguiListboxItem = rb_define_class_under(rb_mCegui,"ListboxItem",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiListboxItem);

	rb_define_method(rb_cCeguiListboxItem,"initialize",RUBY_METHOD_FUNC(_initialize),1);

	rb_define_attr_method(rb_cCeguiListboxItem,"text",_getText,_setText);
	rb_define_attr_method(rb_cCeguiListboxItem,"tooltipText",_getTooltipText,_setTooltipText);
	rb_define_attr_method(rb_cCeguiListboxItem,"ownerWindow",_getOwnerWindow,_setOwnerWindow);
	rb_define_attr_method(rb_cCeguiListboxItem,"id",_getID,_setID);
	rb_define_attr_method(rb_cCeguiListboxItem,"selectionColors",_getSelectionColours,_setSelectionColours);
	rb_define_attr_method(rb_cCeguiListboxItem,"selectionBrushImage",_getSelectionBrushImage,_setSelectionBrushImage);

	rb_define_attr_method(rb_cCeguiListboxItem,"selected",_getSelected,_setSelected);
	rb_define_attr_method(rb_cCeguiListboxItem,"disabled",_getDisabled,_setDisabled);
	rb_define_attr_method(rb_cCeguiListboxItem,"autodeleted",_getAutoDeleted,_setAutoDeleted);

	rb_define_method(rb_cCeguiListboxItem,"<=>",RUBY_METHOD_FUNC(_compare),1);
	rb_include_module(rb_cCeguiListboxItem,rb_mComparable);
	
	rb_define_method(rb_cCeguiListboxItem,"draw",RUBY_METHOD_FUNC(_draw),4);
	
	rb_define_singleton_method(rb_cCeguiListboxItem,"defaultSelectionColor",RUBY_METHOD_FUNC(_single_getDefaultSelectionColour),0);
	rb_define_singleton_method(rb_cCeguiListboxItem,"defaultSelectionColor=",RUBY_METHOD_FUNC(_single_setDefaultSelectionColour),1);
}
