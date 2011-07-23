#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Checkbox*>(self)
VALUE rb_cCeguiCheckbox;


/*
*/
VALUE CeguiCheckbox_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Checkbox::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
VALUE CeguiCheckbox_getSelected(VALUE self)
{
	return RBOOL(_self->isSelected());
}
/*
*/
VALUE CeguiCheckbox_setSelected(VALUE self,VALUE val)
{
	_self->setSelected(RTEST(val));
	return val;
}


/*
*/
void Init_CeguiCheckbox(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiButtonBase = rb_define_class_under(rb_mCegui,"ButtonBase",rb_cCeguiButtonBase);

#endif

	rb_cCeguiCheckbox = rb_define_class_under(rb_mCegui,"Checkbox",rb_cCeguiButtonBase);

	rb_define_singleton_method(rb_cCeguiCheckbox,"new",RUBY_METHOD_FUNC(CeguiCheckbox_new),-1);
	rb_define_attr_method(rb_cCeguiCheckbox,"selected",CeguiCheckbox_getSelected,CeguiCheckbox_setSelected);
	
	rb_define_const(rb_cCeguiCheckbox,"WidgetTypeName",wrap(CEGUI::Checkbox::WidgetTypeName));	
	rb_define_const(rb_cCeguiCheckbox,"EventNamespace",wrap(CEGUI::Checkbox::EventNamespace));
	
	rb_define_const(rb_cCeguiCheckbox,"EventCheckStateChanged",wrap(CEGUI::Checkbox::EventCheckStateChanged));

}
