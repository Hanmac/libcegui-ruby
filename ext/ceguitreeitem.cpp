#include "ceguiwindow.hpp"
#include "ceguitreeitem.hpp"
#include "ceguirect.hpp"
#include "ceguiexception.hpp"
#define _self wrap<CEGUI::TreeItem*>(self)
VALUE rb_cCeguiTreeItem;
namespace CeguiTreeItem {

macro_attr(Font,CEGUI::Font*)
macro_attr(Text,CEGUI::String)
macro_attr(TooltipText,CEGUI::String)


macro_attr(TextColours,CEGUI::ColourRect)
macro_attr(SelectionColours,CEGUI::ColourRect)

macro_attr(SelectionBrushImage,CEGUI::Image*)

macro_attr(OwnerWindow,CEGUI::Window*)

macro_attr_bool(Selected)
macro_attr_bool(Disabled)

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::TreeItem(""));
}
/*
*/
VALUE _addItem(VALUE self,VALUE item)
{
	try{
		_self->addItem(wrap<CEGUI::TreeItem*>(item));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}
/*
*/
VALUE _removeItem(VALUE self,VALUE item)
{
	_self->removeItem(wrap<CEGUI::TreeItem*>(item));
	return self;
}

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getItemCount(); ++i)
	{
		rb_yield(wrap(_self->getTreeItemFromIndex(i)));
	}
	return self;
}

/*
*/
VALUE _compare(VALUE self,VALUE other)
{
	if (rb_obj_is_kind_of(other, rb_cCeguiTreeItem)){
		CEGUI::TreeItem *cother = wrap<CEGUI::TreeItem*>(other);
		return INT2NUM(*_self > *cother ? 1 : *_self < *cother ? -1 : 0);
	}else{
		return Qnil;
	}
}


/*
*/
VALUE _getButtonLocation(VALUE self)
{
	return wrap(_self->getButtonLocation());
}

/*
*/
VALUE _setButtonLocation(VALUE self,VALUE val)
{
	CEGUI::Rectf temp(wrap<CEGUI::Rectf>(val));
	_self->setButtonLocation(temp);
	return val;
}


}
/*
*/
void Init_CeguiTreeItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");


	rb_define_attr(rb_cCeguiTreeItem,"font",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"text",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"tooltipText",1,1);
	
	rb_define_attr(rb_cCeguiTreeItem,"textColours",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"selectionColours",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"selectionBrushImage",1,1);
	
	rb_define_attr(rb_cCeguiTreeItem,"ownerWindow",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"buttonLocation",1,1);

	rb_define_attr(rb_cCeguiTreeItem,"selected",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"disabled",1,1);
#endif
	using namespace CeguiTreeItem;

	rb_cCeguiTreeItem = rb_define_class_under(rb_mCegui,"TreeItem",rb_cObject);
	

	rb_define_attr_method(rb_cCeguiTreeItem,"font",_getFont,_setFont);
	rb_define_attr_method(rb_cCeguiTreeItem,"text",_getText,_setText);
	rb_define_attr_method(rb_cCeguiTreeItem,"tooltipText",_getTooltipText,_setTooltipText);
	
	rb_define_attr_method(rb_cCeguiTreeItem,"textColours",_getTextColours,_setTextColours);
	rb_define_attr_method(rb_cCeguiTreeItem,"selectionColours",_getSelectionColours,_setSelectionColours);
	rb_define_attr_method(rb_cCeguiTreeItem,"selectionBrushImage",_getSelectionBrushImage,_setSelectionBrushImage);
	
	rb_define_attr_method(rb_cCeguiTreeItem,"ownerWindow",_getOwnerWindow,_setOwnerWindow);
	rb_define_attr_method(rb_cCeguiTreeItem,"buttonLocation",_getButtonLocation,_setButtonLocation);

	rb_define_attr_method(rb_cCeguiTreeItem,"selected",_getSelected,_setSelected);
	rb_define_attr_method(rb_cCeguiTreeItem,"disabled",_getDisabled,_setDisabled);
	
	rb_define_alloc_func(rb_cCeguiTreeItem,_alloc);

	rb_define_method(rb_cCeguiTreeItem,"each",RUBY_METHOD_FUNC(_each),0);
	rb_define_method(rb_cCeguiTreeItem,"<=>",RUBY_METHOD_FUNC(_compare),1);
	rb_include_module(rb_cCeguiWindow,rb_mEnumerable);
	rb_include_module(rb_cCeguiWindow,rb_mComparable);
	
	rb_define_method(rb_cCeguiTreeItem,"addItem",RUBY_METHOD_FUNC(_addItem),1);
	rb_define_method(rb_cCeguiTreeItem,"removeItem",RUBY_METHOD_FUNC(_removeItem),1);


}
