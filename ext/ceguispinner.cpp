/*
 * ceguispinner.cpp
 *
 *  Created on: 05.12.2011
 *      Author: hanmac
 */
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Spinner*>(self)
VALUE rb_cCeguiSpinner;
namespace CeguiSpinner {

macro_attr(CurrentValue,float)
macro_attr(MaximumValue,float)
macro_attr(MinimumValue,float)
macro_attr(StepSize,float)

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Spinner::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}


/*
*/
VALUE _getIncreaseButton(VALUE self)
{
	return wrap(_self->getChild(CEGUI::Spinner::IncreaseButtonName));
}
/*
*/
VALUE _getDecreaseButton(VALUE self)
{
	return wrap(_self->getChild(CEGUI::Spinner::DecreaseButtonName));
}
/*
*/
VALUE _getEditbox(VALUE self)
{
	return wrap(_self->getChild(CEGUI::Spinner::EditboxName));
}




}

/*
*/
void Init_CeguiSpinner(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiSpinner,"currentValue",1,1);
	rb_define_attr(rb_cCeguiSpinner,"maximumValue",1,1);
	rb_define_attr(rb_cCeguiSpinner,"minimumValue",1,1);
	rb_define_attr(rb_cCeguiSpinner,"stepSize",1,1);

#endif
	using namespace CeguiSpinner;

	rb_cCeguiSpinner = rb_define_class_under(rb_mCegui,"Spinner",rb_cCeguiWindow);


	rb_define_attr_method(rb_cCeguiSpinner,"currentValue",_getCurrentValue,_setCurrentValue);
	rb_define_attr_method(rb_cCeguiSpinner,"maximumValue",_getMaximumValue,_setMaximumValue);
	rb_define_attr_method(rb_cCeguiSpinner,"minimumValue",_getMinimumValue,_setMinimumValue);
	rb_define_attr_method(rb_cCeguiSpinner,"stepSize",_getStepSize,_setStepSize);

	rb_define_singleton_method(rb_cCeguiSpinner,"new",RUBY_METHOD_FUNC(_new),-1);

//rb_define_method(rb_cCeguiSpinner,"thumb",RUBY_METHOD_FUNC(_getThumb),0);

	rb_define_const(rb_cCeguiSpinner,"WidgetTypeName",wrap(CEGUI::Spinner::WidgetTypeName));
	rb_define_const(rb_cCeguiSpinner,"EventNamespace",wrap(CEGUI::Spinner::EventNamespace));

	rb_define_const(rb_cCeguiSpinner,"EventValueChanged",wrap(CEGUI::Spinner::EventValueChanged));
	rb_define_const(rb_cCeguiSpinner,"EventStepChanged",wrap(CEGUI::Spinner::EventStepChanged));
	rb_define_const(rb_cCeguiSpinner,"EventMaximumValueChanged",wrap(CEGUI::Spinner::EventMaximumValueChanged));
	rb_define_const(rb_cCeguiSpinner,"EventMinimumValueChanged",wrap(CEGUI::Spinner::EventMinimumValueChanged));
	rb_define_const(rb_cCeguiSpinner,"EventTextInputModeChanged",wrap(CEGUI::Spinner::EventTextInputModeChanged));
	rb_define_const(rb_cCeguiSpinner,"EditboxName",wrap(CEGUI::Spinner::EditboxName));
	rb_define_const(rb_cCeguiSpinner,"IncreaseButtonName",wrap(CEGUI::Spinner::IncreaseButtonName));
	rb_define_const(rb_cCeguiSpinner,"DecreaseButtonName",wrap(CEGUI::Spinner::DecreaseButtonName));

}
