#include "ceguitooltip.hpp"
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Tooltip*>(self)
VALUE rb_cCeguiTooltip;

namespace CeguiTooltip {

macro_attr(TargetWindow,CEGUI::Window*)

macro_attr(DisplayTime,float)
macro_attr(HoverTime,float)
macro_attr(FadeTime,float)


/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Tooltip::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

}
/*
*/
void Init_CeguiTooltip(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiTooltip,"targetWindow",1,1);

	rb_define_attr(rb_cCeguiTooltip,"displayTime",1,1);
	rb_define_attr(rb_cCeguiTooltip,"hoverTime",1,1);
	rb_define_attr(rb_cCeguiTooltip,"fadeTime",1,1);
#endif
	using namespace CeguiTooltip;

	rb_cCeguiTooltip = rb_define_class_under(rb_mCegui,"Tooltip",rb_cCeguiWindow);
	
	rb_define_attr_method(rb_cCeguiTooltip,"targetWindow",_getTargetWindow,_setTargetWindow);

	rb_define_attr_method(rb_cCeguiTooltip,"displayTime",_getDisplayTime,_setDisplayTime);
	rb_define_attr_method(rb_cCeguiTooltip,"hoverTime",_getHoverTime,_setHoverTime);
	rb_define_attr_method(rb_cCeguiTooltip,"fadeTime",_getFadeTime,_setFadeTime);

	rb_define_singleton_method(rb_cCeguiTooltip,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiTooltip,"WidgetTypeName",wrap(CEGUI::Tooltip::WidgetTypeName));	
	rb_define_const(rb_cCeguiTooltip,"EventNamespace",wrap(CEGUI::Tooltip::EventNamespace));
	
	rb_define_const(rb_cCeguiTooltip,"EventHoverTimeChanged",wrap(CEGUI::Tooltip::EventHoverTimeChanged));
	rb_define_const(rb_cCeguiTooltip,"EventDisplayTimeChanged",wrap(CEGUI::Tooltip::EventDisplayTimeChanged));
	rb_define_const(rb_cCeguiTooltip,"EventFadeTimeChanged",wrap(CEGUI::Tooltip::EventFadeTimeChanged));
	rb_define_const(rb_cCeguiTooltip,"EventTooltipActive",wrap(CEGUI::Tooltip::EventTooltipActive));
	rb_define_const(rb_cCeguiTooltip,"EventTooltipInactive",wrap(CEGUI::Tooltip::EventTooltipInactive));
}
