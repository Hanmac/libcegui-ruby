#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Scrollbar*>(self)
VALUE rb_cCeguiScrollbar;

macro_attr_with_func(Scrollbar,DocumentSize,DBL2NUM,NUM2DBL)
macro_attr_with_func(Scrollbar,PageSize,DBL2NUM,NUM2DBL)
macro_attr_with_func(Scrollbar,StepSize,DBL2NUM,NUM2DBL)
macro_attr_with_func(Scrollbar,OverlapSize,DBL2NUM,NUM2DBL)
macro_attr_with_func(Scrollbar,ScrollPosition,DBL2NUM,NUM2DBL)

/*
*/
VALUE CeguiScrollbar_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Scrollbar::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

/*
*/
VALUE CeguiScrollbar_getIncreaseButton(VALUE self)
{
	return wrap(_self->getIncreaseButton());
}
/*
*/
VALUE CeguiScrollbar_getDecreaseButton(VALUE self)
{
	return wrap(_self->getDecreaseButton());
}
/*
*/
VALUE CeguiScrollbar_getThumb(VALUE self)
{
	return wrap(_self->getThumb());
}


/*
*/
void Init_CeguiScrollbar(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiScrollbar,"documentSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"pageSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"stepSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"overlapSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"scrollPosition",1,1);

#endif

	rb_cCeguiScrollbar = rb_define_class_under(rb_mCegui,"Scrollbar",rb_cCeguiWindow);
	

	rb_define_attr_method(rb_cCeguiScrollbar,"documentSize",CeguiScrollbar_getDocumentSize,CeguiScrollbar_setDocumentSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"pageSize",CeguiScrollbar_getPageSize,CeguiScrollbar_setPageSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"stepSize",CeguiScrollbar_getStepSize,CeguiScrollbar_setStepSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"overlapSize",CeguiScrollbar_getOverlapSize,CeguiScrollbar_setOverlapSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"scrollPosition",CeguiScrollbar_getScrollPosition,CeguiScrollbar_setScrollPosition);

	rb_define_singleton_method(rb_cCeguiScrollbar,"new",RUBY_METHOD_FUNC(CeguiScrollbar_new),-1);

	rb_define_method(rb_cCeguiScrollbar,"increaseButton",RUBY_METHOD_FUNC(CeguiScrollbar_getIncreaseButton),0);
	rb_define_method(rb_cCeguiScrollbar,"decreaseButton",RUBY_METHOD_FUNC(CeguiScrollbar_getDecreaseButton),0);

	rb_define_method(rb_cCeguiScrollbar,"thumb",RUBY_METHOD_FUNC(CeguiScrollbar_getThumb),0);	

	rb_define_const(rb_cCeguiScrollbar,"WidgetTypeName",wrap(CEGUI::Scrollbar::WidgetTypeName));	
	rb_define_const(rb_cCeguiScrollbar,"EventNamespace",wrap(CEGUI::Scrollbar::EventNamespace));

	rb_define_const(rb_cCeguiScrollbar,"EventScrollPositionChanged",wrap(CEGUI::Scrollbar::EventScrollPositionChanged));
	rb_define_const(rb_cCeguiScrollbar,"EventThumbTrackStarted",wrap(CEGUI::Scrollbar::EventThumbTrackStarted));
	rb_define_const(rb_cCeguiScrollbar,"EventThumbTrackEnded",wrap(CEGUI::Scrollbar::EventThumbTrackEnded));
	rb_define_const(rb_cCeguiScrollbar,"EventScrollConfigChanged",wrap(CEGUI::Scrollbar::EventScrollConfigChanged));
	rb_define_const(rb_cCeguiScrollbar,"ThumbNameSuffix",wrap(CEGUI::Scrollbar::ThumbNameSuffix));
	rb_define_const(rb_cCeguiScrollbar,"IncreaseButtonNameSuffix",wrap(CEGUI::Scrollbar::IncreaseButtonNameSuffix));
	rb_define_const(rb_cCeguiScrollbar,"DecreaseButtonNameSuffix",wrap(CEGUI::Scrollbar::DecreaseButtonNameSuffix));

}
