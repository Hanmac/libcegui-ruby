#include "ceguilistboxitem.hpp"

#include "ceguifont.hpp"
#include "ceguicolorrect.hpp"
#define _self wrap<CEGUI::ListboxTextItem*>(self)
VALUE rb_cCeguiListboxTextItem;

VALUE CeguiListboxTextItem_alloc(VALUE self)
{
	return wrap(new CEGUI::ListboxTextItem(""));
}

macro_attr(ListboxTextItem,Font,CEGUI::Font*)
macro_attr(ListboxTextItem,TextColours,CEGUI::ColourRect)

/*
*/
VALUE CeguiListboxTextItem_single_getDefaultTextColour(VALUE self)
{
	return wrap(CEGUI::ListboxTextItem::DefaultTextColour);
}
/*
*/
VALUE CeguiListboxTextItem_single_setDefaultTextColour(VALUE self,VALUE value)
{
	const_cast<CEGUI::colour*>(&CEGUI::ListboxTextItem::DefaultTextColour)->setRGB(wrap<CEGUI::colour>(value));
	return value;
}
/*
 * Document-class: CEGUI::ListboxTextItem
 * 
 * This class represents an Listbox TextItem.
*/
void Init_CeguiListboxTextItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiListboxItem,"text",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"ownerWindow",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"id",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"selectionColors",1,1);
	
	rb_define_attr(rb_cCeguiListboxItem,"selectionBrushImage",1,1);

	rb_cCeguiListboxItem = rb_define_class_under(rb_mCegui,"ListboxItem",rb_cObject);
#endif
	rb_cCeguiListboxTextItem = rb_define_class_under(rb_mCegui,"ListboxTextItem",rb_cCeguiListboxItem);
	rb_define_alloc_func(rb_cCeguiListboxTextItem,CeguiListboxTextItem_alloc);

	rb_define_attr_method(rb_cCeguiListboxItem,"font",CeguiListboxTextItem_getFont,CeguiListboxTextItem_setFont);
	rb_define_attr_method(rb_cCeguiListboxItem,"textColors",CeguiListboxTextItem_getTextColours,CeguiListboxTextItem_setTextColours);

	rb_define_singleton_method(rb_cCeguiListboxTextItem,"defaultTextColor",RUBY_METHOD_FUNC(CeguiListboxTextItem_single_getDefaultTextColour),0);
	rb_define_singleton_method(rb_cCeguiListboxTextItem,"defaultTextColor=",RUBY_METHOD_FUNC(CeguiListboxTextItem_single_setDefaultTextColour),1);

}
