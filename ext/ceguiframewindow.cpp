#include "ceguiwindow.hpp"
#include "ceguiexception.hpp"
#define _self wrap<CEGUI::FrameWindow*>(self)
#define _klass CeguiFrameWindow
VALUE rb_cCeguiFrameWindow;

namespace CeguiFrameWindow {

macro_attr(NSSizingCursorImage,CEGUI::Image*)
macro_attr(EWSizingCursorImage,CEGUI::Image*)
macro_attr(NWSESizingCursorImage,CEGUI::Image*)
macro_attr(NESWSizingCursorImage,CEGUI::Image*)


macro_attr_bool(SizingEnabled)
macro_attr_bool(FrameEnabled)
macro_attr_bool(TitleBarEnabled)
macro_attr_bool(CloseButtonEnabled)
macro_attr_bool(RollupEnabled)
macro_attr_bool(Rolledup)
macro_attr_bool(DragMovingEnabled)


/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::FrameWindow::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}
/*
*/
VALUE _getTitlebar(VALUE self)
{
return wrap(_self->getTitlebar());
}
/*
*/
VALUE _getCloseButton(VALUE self)
{
return wrap(_self->getCloseButton());
}
}
/*
*/
void Init_CeguiFrameWindow(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiFrameWindow,"NSSizingCursorImage",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"EWSizingCursorImage",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"NWSESizingCursorImage",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"NESWSizingCursorImage",1,1);

	rb_define_attr(rb_cCeguiFrameWindow,"sizing_enabled",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"frame_enabled",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"titlebar_enabled",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"closebutton_enabled",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"rollup_enabled",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"rolledup",1,1);
	rb_define_attr(rb_cCeguiFrameWindow,"dragmoving_enabled",1,1);

#endif

	using namespace CeguiFrameWindow;

	rb_cCeguiFrameWindow = rb_define_class_under(rb_mCegui,"FrameWindow",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiFrameWindow,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_attr_method(rb_cCeguiFrameWindow,"NSSizingCursorImage",
		_getNSSizingCursorImage,_setNSSizingCursorImage);
	rb_define_attr_method(rb_cCeguiFrameWindow,"EWSizingCursorImage",
		_getEWSizingCursorImage,_setEWSizingCursorImage);
	rb_define_attr_method(rb_cCeguiFrameWindow,"NWSESizingCursorImage",
		_getNWSESizingCursorImage,_setNWSESizingCursorImage);
	rb_define_attr_method(rb_cCeguiFrameWindow,"NESWSizingCursorImage",
		_getNESWSizingCursorImage,_setNESWSizingCursorImage);

	rb_define_attr_method(rb_cCeguiFrameWindow,"sizing_enabled",_getSizingEnabled,_setSizingEnabled);
	rb_define_attr_method(rb_cCeguiFrameWindow,"frame_enabled",_getFrameEnabled,_setFrameEnabled);
	rb_define_attr_method(rb_cCeguiFrameWindow,"titlebar_enabled",
		_getTitleBarEnabled,_setTitleBarEnabled);
	rb_define_attr_method(rb_cCeguiFrameWindow,"closebutton_enabled",
		_getCloseButtonEnabled,_setCloseButtonEnabled);
	rb_define_attr_method(rb_cCeguiFrameWindow,"rollup_enabled",_getRollupEnabled,_setRollupEnabled);
	rb_define_attr_method(rb_cCeguiFrameWindow,"rolledup",_getRolledup,_setRolledup);
	rb_define_attr_method(rb_cCeguiFrameWindow,"dragmoving_enabled",
		_getDragMovingEnabled,_setDragMovingEnabled);


	rb_define_const(rb_cCeguiFrameWindow,"EventNamespace",wrap(CEGUI::FrameWindow::EventNamespace));
	rb_define_const(rb_cCeguiFrameWindow,"WidgetTypeName",wrap(CEGUI::FrameWindow::WidgetTypeName));

	rb_define_const(rb_cCeguiFrameWindow,"EventRollupToggled",wrap(CEGUI::FrameWindow::EventRollupToggled));
	rb_define_const(rb_cCeguiFrameWindow,"EventCloseClicked",wrap(CEGUI::FrameWindow::EventCloseClicked));
	rb_define_const(rb_cCeguiFrameWindow,"EventDragSizingStarted",wrap(CEGUI::FrameWindow::EventDragSizingStarted));
	rb_define_const(rb_cCeguiFrameWindow,"EventDragSizingEnded",wrap(CEGUI::FrameWindow::EventDragSizingEnded));
	rb_define_const(rb_cCeguiFrameWindow,"DefaultSizingBorderSize",DBL2NUM(CEGUI::FrameWindow::DefaultSizingBorderSize));
	rb_define_const(rb_cCeguiFrameWindow,"TitlebarName",wrap(CEGUI::FrameWindow::TitlebarName));
	rb_define_const(rb_cCeguiFrameWindow,"CloseButtonName",wrap(CEGUI::FrameWindow::CloseButtonName));
}
