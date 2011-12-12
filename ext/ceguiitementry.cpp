#include "ceguiitementry.hpp"

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::ItemEntry*>(self)
VALUE rb_cCeguiItemEntry;

namespace CeguiItemEntry {

macro_attr_bool(Selected)
macro_attr_bool(Selectable)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	if(argc==2)
		return rb_call_super(2,argv);
	else{
		VALUE name;
		rb_scan_args(argc, argv, "01",&name);
		VALUE result[2];
		result[0]=wrap(CEGUI::String(CEGUI::ItemEntry::WidgetTypeName));
		result[1]=name;
		return rb_call_super(2,result);
	}
}

}
/*
*/
void Init_CeguiItemEntry(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiItemEntry,"selected",1,1);
	rb_define_attr(rb_cCeguiItemEntry,"selectable",1,1);

#endif
	using namespace CeguiItemEntry;

	rb_cCeguiItemEntry = rb_define_class_under(rb_mCegui,"ItemEntry",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiItemEntry,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_attr_method(rb_cCeguiItemEntry,"selected",_getSelected,_setSelected);
	rb_define_attr_method(rb_cCeguiItemEntry,"selectable",_getSelectable,_setSelectable);
	
	rb_define_const(rb_cCeguiItemEntry,"WidgetTypeName",wrap(CEGUI::ItemEntry::WidgetTypeName));	
	
	rb_define_const(rb_cCeguiItemEntry,"EventSelectionChanged",wrap(CEGUI::ItemEntry::EventSelectionChanged));

}
