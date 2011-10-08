#include "ceguiwindow.hpp"
#include "ceguitreeitem.hpp"
#include "ceguirect.hpp"

#define _self wrap<CEGUI::TreeItem*>(self)
VALUE rb_cCeguiTreeItem;

macro_attr(TreeItem,Font,CEGUI::Font*)
macro_attr(TreeItem,Text,CEGUI::String)
macro_attr(TreeItem,TooltipText,CEGUI::String)


macro_attr(TreeItem,TextColours,CEGUI::ColourRect)
macro_attr(TreeItem,SelectionColours,CEGUI::ColourRect)

macro_attr(TreeItem,SelectionBrushImage,CEGUI::Image*)

macro_attr(TreeItem,OwnerWindow,CEGUI::Window*)
//macro_attr(TreeItem,ButtonLocation,CEGUI::Rectf)


VALUE CeguiTreeItem_alloc(VALUE self)
{
	return wrap(new CEGUI::TreeItem(""));
}
/*
*/
VALUE CeguiTreeItem_addItem(VALUE self,VALUE item)
{
	try{
		_self->addItem(wrap<CEGUI::TreeItem*>(item));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
	}
	return self;
}
/*
*/
VALUE CeguiTreeItem_removeItem(VALUE self,VALUE item)
{
	_self->removeItem(wrap<CEGUI::TreeItem*>(item));
	return self;
}

/*
*/
VALUE CeguiTreeItem_each(VALUE self)
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
VALUE CeguiTreeItem_compare(VALUE self,VALUE other)
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
VALUE CeguiTreeItem_getButtonLocation(VALUE self)
{
	return wrap(_self->getButtonLocation());
}

/*
*/
VALUE CeguiTreeItem_setButtonLocation(VALUE self,VALUE val)
{
	CEGUI::Rectf temp(wrap<CEGUI::Rectf>(val));
	_self->setButtonLocation(temp);
	return val;
}



/*
*/
void Init_CeguiTreeItem(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");


	rb_define_attr(rb_cCeguiTreeItem,"font",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"text",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"tooltipText",1,1);
	
	rb_define_attr(rb_cCeguiTreeItem,"textColours",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"selectionColours",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"selectionBrushImage",1,1);
	
	rb_define_attr(rb_cCeguiTreeItem,"ownerWindow",1,1);
	rb_define_attr(rb_cCeguiTreeItem,"buttonLocation",1,1);
#endif

	rb_cCeguiTreeItem = rb_define_class_under(rb_mCegui,"TreeItem",rb_cObject);
	

	rb_define_attr_method(rb_cCeguiTreeItem,"font",CeguiTreeItem_getFont,CeguiTreeItem_setFont);
	rb_define_attr_method(rb_cCeguiTreeItem,"text",CeguiTreeItem_getText,CeguiTreeItem_setText);
	rb_define_attr_method(rb_cCeguiTreeItem,"tooltipText",CeguiTreeItem_getTooltipText,CeguiTreeItem_setTooltipText);
	
	rb_define_attr_method(rb_cCeguiTreeItem,"textColours",CeguiTreeItem_getTextColours,CeguiTreeItem_setTextColours);
	rb_define_attr_method(rb_cCeguiTreeItem,"selectionColours",CeguiTreeItem_getSelectionColours,CeguiTreeItem_setSelectionColours);
	rb_define_attr_method(rb_cCeguiTreeItem,"selectionBrushImage",CeguiTreeItem_getSelectionBrushImage,CeguiTreeItem_setSelectionBrushImage);
	
	rb_define_attr_method(rb_cCeguiTreeItem,"ownerWindow",CeguiTreeItem_getOwnerWindow,CeguiTreeItem_setOwnerWindow);
	rb_define_attr_method(rb_cCeguiTreeItem,"buttonLocation",CeguiTreeItem_getButtonLocation,CeguiTreeItem_setButtonLocation);
	
	rb_define_alloc_func(rb_cCeguiTreeItem,CeguiTreeItem_alloc);

	rb_define_method(rb_cCeguiTreeItem,"each",RUBY_METHOD_FUNC(CeguiTreeItem_each),0);
	rb_define_method(rb_cCeguiTreeItem,"<=>",RUBY_METHOD_FUNC(CeguiTreeItem_compare),1);
	rb_include_module(rb_cCeguiWindow,rb_mEnumerable);
	rb_include_module(rb_cCeguiWindow,rb_mComparable);
	
	rb_define_method(rb_cCeguiTreeItem,"addItem",RUBY_METHOD_FUNC(CeguiTreeItem_addItem),1);
	rb_define_method(rb_cCeguiTreeItem,"removeItem",RUBY_METHOD_FUNC(CeguiTreeItem_removeItem),1);


}
