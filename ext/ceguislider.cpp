/*
 * ceguislider.cpp
 *
 *  Created on: 05.12.2011
 *      Author: hanmac
 */

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Slider*>(self)
VALUE rb_cCeguiSlider;
namespace CeguiSlider {

macro_attr(CurrentValue,float)
macro_attr(MaxValue,float)
macro_attr(ClickStep,float)

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Slider::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}
/*
*/
VALUE _getThumb(VALUE self)
{
	return wrap(_self->getThumb());
}

}

/*
*/
void Init_CeguiSlider(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiSlider,"currentValue",1,1);
	rb_define_attr(rb_cCeguiSlider,"maxValue",1,1);
	rb_define_attr(rb_cCeguiSlider,"clickStep",1,1);

#endif
	using namespace CeguiSlider;

	rb_cCeguiSlider = rb_define_class_under(rb_mCegui,"Slider",rb_cCeguiWindow);


	rb_define_attr_method(rb_cCeguiSlider,"currentValue",_getCurrentValue,_setCurrentValue);
	rb_define_attr_method(rb_cCeguiSlider,"maxValue",_getMaxValue,_setMaxValue);
	rb_define_attr_method(rb_cCeguiSlider,"clickStep",_getClickStep,_setClickStep);

	rb_define_singleton_method(rb_cCeguiSlider,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_method(rb_cCeguiSlider,"thumb",RUBY_METHOD_FUNC(_getThumb),0);

	rb_define_const(rb_cCeguiSlider,"WidgetTypeName",wrap(CEGUI::Slider::WidgetTypeName));
	rb_define_const(rb_cCeguiSlider,"EventNamespace",wrap(CEGUI::Slider::EventNamespace));

	rb_define_const(rb_cCeguiSlider,"EventValueChanged",wrap(CEGUI::Slider::EventValueChanged));
	rb_define_const(rb_cCeguiSlider,"EventThumbTrackStarted",wrap(CEGUI::Slider::EventThumbTrackStarted));
	rb_define_const(rb_cCeguiSlider,"EventThumbTrackEnded",wrap(CEGUI::Slider::EventThumbTrackEnded));
	rb_define_const(rb_cCeguiSlider,"ThumbName",wrap(CEGUI::Slider::ThumbName));

}
