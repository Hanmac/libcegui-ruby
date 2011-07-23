#include "ceguilistbox.hpp"

#include "ceguilistboxitem.hpp"

#include "ceguiscrollbar.hpp"
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Listbox*>(self)
VALUE rb_cCeguiListbox;

/*
*/
VALUE CeguiListbox_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Listbox::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
VALUE CeguiListbox_addItem(VALUE self,VALUE item)
{
	_self->addItem(wrap<CEGUI::ListboxItem*>(item));
	return self;
}
/*
*/
VALUE CeguiListbox_removeItem(VALUE self,VALUE item)
{
	_self->removeItem(wrap<CEGUI::ListboxItem*>(item));
	return self;
}


/*
*/
VALUE CeguiListbox_each_item(VALUE self)
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
VALUE CeguiListbox_each_selected(VALUE self)
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
VALUE CeguiListbox_getVertScrollbar(VALUE self)
{
	return wrap(_self->getVertScrollbar());
}
/*
*/
VALUE CeguiListbox_getHorzScrollbar(VALUE self)
{
	return wrap(_self->getHorzScrollbar());
}

/*
*/
void Init_CeguiListbox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

#endif

	rb_cCeguiListbox = rb_define_class_under(rb_mCegui,"Listbox",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiListbox,"new",RUBY_METHOD_FUNC(CeguiListbox_new),-1);



	rb_define_method(rb_cCeguiListbox,"addItem",RUBY_METHOD_FUNC(CeguiListbox_addItem),1);
	rb_define_method(rb_cCeguiListbox,"removeItem",RUBY_METHOD_FUNC(CeguiListbox_removeItem),1);
	
	rb_define_method(rb_cCeguiListbox,"each_item",RUBY_METHOD_FUNC(CeguiListbox_each_item),0);
	rb_define_method(rb_cCeguiListbox,"each_selected",RUBY_METHOD_FUNC(CeguiListbox_each_selected),0);
	
	rb_define_method(rb_cCeguiListbox,"vertScrollbar",RUBY_METHOD_FUNC(CeguiListbox_getVertScrollbar),0);
	rb_define_method(rb_cCeguiListbox,"horzScrollbar",RUBY_METHOD_FUNC(CeguiListbox_getHorzScrollbar),0);
	
	
	rb_define_const(rb_cCeguiListbox,"EventNamespace",wrap(CEGUI::Listbox::EventNamespace));
	rb_define_const(rb_cCeguiListbox,"WidgetTypeName",wrap(CEGUI::Listbox::WidgetTypeName));	
	
	rb_define_const(rb_cCeguiListbox,"EventListContentsChanged",wrap(CEGUI::Listbox::EventListContentsChanged));
	rb_define_const(rb_cCeguiListbox,"EventSelectionChanged",wrap(CEGUI::Listbox::EventSelectionChanged));
	rb_define_const(rb_cCeguiListbox,"EventSortModeChanged",wrap(CEGUI::Listbox::EventSortModeChanged));
	rb_define_const(rb_cCeguiListbox,"EventMultiselectModeChanged",wrap(CEGUI::Listbox::EventMultiselectModeChanged));
	rb_define_const(rb_cCeguiListbox,"EventVertScrollbarModeChanged",wrap(CEGUI::Listbox::EventVertScrollbarModeChanged));
	rb_define_const(rb_cCeguiListbox,"EventHorzScrollbarModeChanged",wrap(CEGUI::Listbox::EventHorzScrollbarModeChanged));

	rb_define_const(rb_cCeguiListbox,"VertScrollbarNameSuffix",wrap(CEGUI::Listbox::VertScrollbarNameSuffix));
	rb_define_const(rb_cCeguiListbox,"HorzScrollbarNameSuffix",wrap(CEGUI::Listbox::HorzScrollbarNameSuffix));	

}
