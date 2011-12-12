#include "ceguilistbox.hpp"

#include "ceguilistboxitem.hpp"

#include "ceguiscrollbar.hpp"
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Listbox*>(self)
VALUE rb_cCeguiListbox;

namespace CeguiListbox {

macro_attr_bool(MultiselectEnabled)
macro_attr_bool(ItemTooltipsEnabled)

singlefunc(resetList)

VALUE _getSortEnabled(VALUE self)
{
	return wrap(_self->isSortEnabled());
}
VALUE _setSortEnabled(VALUE self,VALUE val)
{
	_self->setSortingEnabled(wrap<bool>(val));
	return val;
}

VALUE _getShowVertScrollbar(VALUE self)
{
	return wrap(_self->isVertScrollbarAlwaysShown());
}
VALUE _setShowVertScrollbar(VALUE self,VALUE val)
{
	_self->setShowVertScrollbar(wrap<bool>(val));
	return val;
}

VALUE _getShowHorzScrollbar(VALUE self)
{
	return wrap(_self->isHorzScrollbarAlwaysShown());
}
VALUE _setShowHorzScrollbar(VALUE self,VALUE val)
{
	_self->setShowHorzScrollbar(wrap<bool>(val));
	return val;
}

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	if(argc==2)
		return rb_call_super(2,argv);
	else{
		rb_scan_args(argc, argv, "01",&name);
		VALUE result[2];
		result[0]=wrap(CEGUI::String(CEGUI::Listbox::WidgetTypeName));
		result[1]=name;
		return rb_call_super(2,result);
	}
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
	}else	if(rb_obj_is_kind_of(pos, rb_cString)){
		CEGUI::ListboxItem* cpos = _self->findItemWithText(wrap<CEGUI::String>(pos),NULL);
		_self->insertItem(cpos,wrap<CEGUI::ListboxItem*>(item));
	}else
		_self->insertItem(_self->getListboxItemFromIndex(NUM2UINT(pos)),wrap<CEGUI::ListboxItem*>(item));
	return self;
}
/*
*/
VALUE _removeItem(VALUE self,VALUE item)
{
	CEGUI::ListboxItem* citem;
	if(rb_obj_is_kind_of(item, rb_cString))
		citem = _self->findItemWithText(wrap<CEGUI::String>(item),NULL);
	else
		citem = wrap<CEGUI::ListboxItem*>(item);
	if(citem)
		_self->removeItem(citem);
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
/*
*/
VALUE _each_selected(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	CEGUI::ListboxItem *sel = _self->getFirstSelectedItem();
	while (sel)
	{
		rb_yield(wrap(sel));
		sel = _self->getNextSelected(sel);
	}
	return self;
}


/*
*/
VALUE _getVertScrollbar(VALUE self)
{
	return wrap(_self->getVertScrollbar());
}
/*
*/
VALUE _getHorzScrollbar(VALUE self)
{
	return wrap(_self->getHorzScrollbar());
}

}
/* Document-method: clear

*/


/*
*/
void Init_CeguiListbox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiListbox,"multiselectEnabled",1,1);
	rb_define_attr(rb_cCeguiListbox,"itemTooltipsEnabled",1,1);

	rb_define_attr(rb_cCeguiListbox,"sortEnabled",1,1);
	rb_define_attr(rb_cCeguiListbox,"showVertScrollbar",1,1);
	rb_define_attr(rb_cCeguiListbox,"showHorzScrollbar",1,1);

#endif
	using namespace CeguiListbox;

	rb_cCeguiListbox = rb_define_class_under(rb_mCegui,"Listbox",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiListbox,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_attr_method(rb_cCeguiListbox,"multiselectEnabled",_getMultiselectEnabled,_setMultiselectEnabled);
	rb_define_attr_method(rb_cCeguiListbox,"itemTooltipsEnabled",_getItemTooltipsEnabled,_setItemTooltipsEnabled);

	rb_define_attr_method(rb_cCeguiListbox,"sortEnabled",_getSortEnabled,_setSortEnabled);
	rb_define_attr_method(rb_cCeguiListbox,"showVertScrollbar",_getShowVertScrollbar,_setShowVertScrollbar);
	rb_define_attr_method(rb_cCeguiListbox,"showHorzScrollbar",_getShowHorzScrollbar,_setShowHorzScrollbar);

	rb_define_method(rb_cCeguiListbox,"addItem",RUBY_METHOD_FUNC(_addItem),1);
	rb_define_method(rb_cCeguiListbox,"insertItem",RUBY_METHOD_FUNC(_insertItem),2);
	rb_define_method(rb_cCeguiListbox,"removeItem",RUBY_METHOD_FUNC(_removeItem),1);
	
	rb_define_method(rb_cCeguiListbox,"each_item",RUBY_METHOD_FUNC(_each_item),0);
	rb_define_method(rb_cCeguiListbox,"each_selected",RUBY_METHOD_FUNC(_each_selected),0);
	
	rb_define_method(rb_cCeguiListbox,"vertScrollbar",RUBY_METHOD_FUNC(_getVertScrollbar),0);
	rb_define_method(rb_cCeguiListbox,"horzScrollbar",RUBY_METHOD_FUNC(_getHorzScrollbar),0);
	
	rb_define_method(rb_cCeguiListbox,"clear",RUBY_METHOD_FUNC(_resetList),0);
	
	rb_define_const(rb_cCeguiListbox,"EventNamespace",wrap(CEGUI::Listbox::EventNamespace));
	rb_define_const(rb_cCeguiListbox,"WidgetTypeName",wrap(CEGUI::Listbox::WidgetTypeName));	
	
	rb_define_const(rb_cCeguiListbox,"EventListContentsChanged",wrap(CEGUI::Listbox::EventListContentsChanged));
	rb_define_const(rb_cCeguiListbox,"EventSelectionChanged",wrap(CEGUI::Listbox::EventSelectionChanged));
	rb_define_const(rb_cCeguiListbox,"EventSortModeChanged",wrap(CEGUI::Listbox::EventSortModeChanged));
	rb_define_const(rb_cCeguiListbox,"EventMultiselectModeChanged",wrap(CEGUI::Listbox::EventMultiselectModeChanged));
	rb_define_const(rb_cCeguiListbox,"EventVertScrollbarModeChanged",wrap(CEGUI::Listbox::EventVertScrollbarModeChanged));
	rb_define_const(rb_cCeguiListbox,"EventHorzScrollbarModeChanged",wrap(CEGUI::Listbox::EventHorzScrollbarModeChanged));

	rb_define_const(rb_cCeguiListbox,"VertScrollbarName",wrap(CEGUI::Listbox::VertScrollbarName));
	rb_define_const(rb_cCeguiListbox,"HorzScrollbarName",wrap(CEGUI::Listbox::HorzScrollbarName));	

}
