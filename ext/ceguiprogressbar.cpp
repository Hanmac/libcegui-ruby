/*
 * ceguiprogressbar.cpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */



#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::ProgressBar*>(self)
VALUE rb_cCeguiProgressBar;
namespace CeguiProgressBar {

macro_attr(Progress,float)
macro_attr(StepSize,float)

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::ProgressBar::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}


}

/*
*/
void Init_CeguiProgressBar(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiProgressBar,"progress",1,1);
	rb_define_attr(rb_cCeguiProgressBar,"stepSize",1,1);

#endif
	using namespace CeguiProgressBar;

	rb_cCeguiProgressBar = rb_define_class_under(rb_mCegui,"ProgressBar",rb_cCeguiWindow);


	rb_define_attr_method(rb_cCeguiProgressBar,"progress",_getProgress,_setProgress);
	rb_define_attr_method(rb_cCeguiProgressBar,"stepSize",_getStepSize,_setStepSize);

	rb_define_singleton_method(rb_cCeguiProgressBar,"new",RUBY_METHOD_FUNC(_new),-1);

//	rb_define_method(rb_cCeguiProgressBar,"thumb",RUBY_METHOD_FUNC(_getThumb),0);

	rb_define_const(rb_cCeguiProgressBar,"WidgetTypeName",wrap(CEGUI::ProgressBar::WidgetTypeName));
	rb_define_const(rb_cCeguiProgressBar,"EventNamespace",wrap(CEGUI::ProgressBar::EventNamespace));


	rb_define_const(rb_cCeguiProgressBar,"EventProgressChanged",wrap(CEGUI::ProgressBar::EventProgressChanged));
	rb_define_const(rb_cCeguiProgressBar,"EventProgressDone",wrap(CEGUI::ProgressBar::EventProgressDone));
}

