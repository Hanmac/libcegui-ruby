#include "ceguilistboxitem.hpp"

#include "ceguifont.hpp"
#include "ceguicolorrect.hpp"
#define _self wrap<CEGUI::ListboxTextItem*>(self)
VALUE rb_cCeguiListboxTextItem;
namespace CeguiListboxTextItem {
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::ListboxTextItem(""));
}

macro_attr(Font,CEGUI::Font*)
macro_attr(TextColours,CEGUI::ColourRect)

/*
*/
VALUE _single_getDefaultTextColour(VALUE self)
{
	return wrap(CEGUI::ListboxTextItem::DefaultTextColour);
}
/*
*/
VALUE _single_setDefaultTextColour(VALUE self,VALUE value)
{
	const_cast<CEGUI::Colour*>(&CEGUI::ListboxTextItem::DefaultTextColour)->setRGB(wrap<CEGUI::Colour>(value));
	return value;
}

}
/*
 * Document-class: CEGUI::ListboxTextItem
 * 
 * This class represents an Listbox TextItem.
*/
void Init_CeguiListboxTextItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiListboxItem,"text",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"ownerWindow",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"id",1,1);
	rb_define_attr(rb_cCeguiListboxItem,"selectionColors",1,1);
	
	rb_define_attr(rb_cCeguiListboxItem,"selectionBrushImage",1,1);

	rb_cCeguiListboxItem = rb_define_class_under(rb_mCegui,"ListboxItem",rb_cObject);
#endif
	using namespace CeguiListboxTextItem;
	
	rb_cCeguiListboxTextItem = rb_define_class_under(rb_mCegui,"ListboxTextItem",rb_cCeguiListboxItem);
	rb_define_alloc_func(rb_cCeguiListboxTextItem,_alloc);

	rb_define_attr_method(rb_cCeguiListboxItem,"font",_getFont,_setFont);
	rb_define_attr_method(rb_cCeguiListboxItem,"textColors",_getTextColours,_setTextColours);

	rb_define_singleton_method(rb_cCeguiListboxTextItem,"defaultTextColor",RUBY_METHOD_FUNC(_single_getDefaultTextColour),0);
	rb_define_singleton_method(rb_cCeguiListboxTextItem,"defaultTextColor=",RUBY_METHOD_FUNC(_single_setDefaultTextColour),1);

}
