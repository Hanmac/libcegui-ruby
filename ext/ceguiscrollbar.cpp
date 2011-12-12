#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Scrollbar*>(self)
VALUE rb_cCeguiScrollbar;
namespace CeguiScrollbar {
macro_attr(DocumentSize,float)
macro_attr(PageSize,float)
macro_attr(StepSize,float)
macro_attr(OverlapSize,float)
macro_attr(ScrollPosition,float)

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
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
VALUE _getIncreaseButton(VALUE self)
{
	return wrap(_self->getIncreaseButton());
}
/*
*/
VALUE _getDecreaseButton(VALUE self)
{
	return wrap(_self->getDecreaseButton());
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
void Init_CeguiScrollbar(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiScrollbar,"documentSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"pageSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"stepSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"overlapSize",1,1);
	rb_define_attr(rb_cCeguiScrollbar,"scrollPosition",1,1);

#endif
	using namespace CeguiScrollbar;

	rb_cCeguiScrollbar = rb_define_class_under(rb_mCegui,"Scrollbar",rb_cCeguiWindow);
	

	rb_define_attr_method(rb_cCeguiScrollbar,"documentSize",_getDocumentSize,_setDocumentSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"pageSize",_getPageSize,_setPageSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"stepSize",_getStepSize,_setStepSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"overlapSize",_getOverlapSize,_setOverlapSize);
	rb_define_attr_method(rb_cCeguiScrollbar,"scrollPosition",_getScrollPosition,_setScrollPosition);

	rb_define_singleton_method(rb_cCeguiScrollbar,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_method(rb_cCeguiScrollbar,"increaseButton",RUBY_METHOD_FUNC(_getIncreaseButton),0);
	rb_define_method(rb_cCeguiScrollbar,"decreaseButton",RUBY_METHOD_FUNC(_getDecreaseButton),0);

	rb_define_method(rb_cCeguiScrollbar,"thumb",RUBY_METHOD_FUNC(_getThumb),0);

	rb_define_const(rb_cCeguiScrollbar,"WidgetTypeName",wrap(CEGUI::Scrollbar::WidgetTypeName));	
	rb_define_const(rb_cCeguiScrollbar,"EventNamespace",wrap(CEGUI::Scrollbar::EventNamespace));

	rb_define_const(rb_cCeguiScrollbar,"EventScrollPositionChanged",wrap(CEGUI::Scrollbar::EventScrollPositionChanged));
	rb_define_const(rb_cCeguiScrollbar,"EventThumbTrackStarted",wrap(CEGUI::Scrollbar::EventThumbTrackStarted));
	rb_define_const(rb_cCeguiScrollbar,"EventThumbTrackEnded",wrap(CEGUI::Scrollbar::EventThumbTrackEnded));
	rb_define_const(rb_cCeguiScrollbar,"EventScrollConfigChanged",wrap(CEGUI::Scrollbar::EventScrollConfigChanged));
	rb_define_const(rb_cCeguiScrollbar,"ThumbName",wrap(CEGUI::Scrollbar::ThumbName));
	rb_define_const(rb_cCeguiScrollbar,"IncreaseButtonName",wrap(CEGUI::Scrollbar::IncreaseButtonName));
	rb_define_const(rb_cCeguiScrollbar,"DecreaseButtonName",wrap(CEGUI::Scrollbar::DecreaseButtonName));

}
