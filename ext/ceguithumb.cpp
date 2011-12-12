#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Thumb*>(self)
VALUE rb_cCeguiThumb;

namespace CeguiThumb {

macro_attr_bool(HotTracked)
macro_attr_bool(VertFree)
macro_attr_bool(HorzFree)

macro_attr(VertRange,Range)
macro_attr(HorzRange,Range)
/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Thumb::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

}
/*
*/
void Init_CeguiThumb(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiButtonBase = rb_define_class_under(rb_mCegui,"ButtonBase",rb_cCeguiWindow);
	rb_cCeguiPushButton = rb_define_class_under(rb_mCegui,"PushButton",rb_cCeguiButtonBase);
	
	rb_define_attr(rb_cCeguiThumb,"hotTracked",1,1);
	rb_define_attr(rb_cCeguiThumb,"vertFree",1,1);
	rb_define_attr(rb_cCeguiThumb,"horzFree",1,1);
#endif
	using namespace CeguiThumb;

	rb_cCeguiThumb = rb_define_class_under(rb_mCegui,"Thumb",rb_cCeguiPushButton);

	rb_define_attr_method(rb_cCeguiThumb,"hotTracked",_getHotTracked,_setHotTracked);
	rb_define_attr_method(rb_cCeguiThumb,"vertFree",_getVertFree,_setVertFree);
	rb_define_attr_method(rb_cCeguiThumb,"horzFree",_getHorzFree,_setHorzFree);

	rb_define_attr_method(rb_cCeguiThumb,"vertRange",_getVertRange,_setVertRange);
	rb_define_attr_method(rb_cCeguiThumb,"horzRange",_getHorzRange,_setHorzRange);

	
	rb_define_singleton_method(rb_cCeguiThumb,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiThumb,"WidgetTypeName",wrap(CEGUI::Thumb::WidgetTypeName));
	rb_define_const(rb_cCeguiThumb,"EventNamespace",wrap(CEGUI::Thumb::EventNamespace));
	
	
	rb_define_const(rb_cCeguiThumb,"EventThumbPositionChanged",wrap(CEGUI::Thumb::EventThumbPositionChanged));
	rb_define_const(rb_cCeguiThumb,"EventThumbTrackStarted",wrap(CEGUI::Thumb::EventThumbTrackStarted));
	rb_define_const(rb_cCeguiThumb,"EventThumbTrackEnded",wrap(CEGUI::Thumb::EventThumbTrackEnded));
}
