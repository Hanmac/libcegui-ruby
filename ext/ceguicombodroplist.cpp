#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::ComboDropList*>(self)
VALUE rb_cCeguiComboDropList;

/*
*/
VALUE CeguiComboDropList_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::ComboDropList::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
void Init_CeguiComboDropList(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiListbox = rb_define_class_under(rb_mCegui,"Listbox",rb_cCeguiWindow);
	
#endif

	rb_cCeguiComboDropList = rb_define_class_under(rb_mCegui,"ComboDropList",rb_cCeguiListbox);
	
	rb_define_singleton_method(rb_cCeguiComboDropList,"new",RUBY_METHOD_FUNC(CeguiComboDropList_new),-1);

	rb_define_const(rb_cCeguiComboDropList,"EventNamespace",wrap(CEGUI::ComboDropList::EventNamespace));
	rb_define_const(rb_cCeguiComboDropList,"WidgetTypeName",wrap(CEGUI::ComboDropList::WidgetTypeName));	
	
	rb_define_const(rb_cCeguiComboDropList,"EventListSelectionAccepted",wrap(CEGUI::ComboDropList::EventListSelectionAccepted));

}
