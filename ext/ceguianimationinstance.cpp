/*
 * ceguianimationinstance.cpp
 *
 *  Created on: 18.12.2011
 *      Author: hanmac
 */
#include "ceguianimation.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::AnimationInstance*>(self)

VALUE rb_cCeguiAnimationInstance;
namespace CeguiAnimationInstance {

macro_attr(Target,CEGUI::PropertySet*)
macro_attr(EventReceiver,CEGUI::EventSet*)
macro_attr(EventSender,CEGUI::EventSet*)

macro_attr(Position,float)
macro_attr(Speed,float)
macro_attr(SkipNextStep,bool)
macro_attr(MaxStepDeltaSkip,float)
macro_attr(MaxStepDeltaClamp,float)

singlefunc(stop)
singlefunc(pause)

singlereturn(isRunning)

VALUE _step(VALUE self,VALUE delta)
{
	_self->step(NUM2DBL(delta));
	return self;
}
}
/*
 *
 */
void Init_CeguiAnimationInstance(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiAnimationInstance,"target",1,1);
	rb_define_attr(rb_cCeguiAnimationInstance,"eventReceiver",1,1);
	rb_define_attr(rb_cCeguiAnimationInstance,"eventSender",1,1);

	rb_define_attr(rb_cCeguiAnimationInstance,"position",1,1);

	rb_define_attr(rb_cCeguiAnimationInstance,"speed",1,1);

	rb_define_attr(rb_cCeguiAnimationInstance,"skipNextStep",1,1);

	rb_define_attr(rb_cCeguiAnimationInstance,"maxStepDeltaSkip",1,1);

	rb_define_attr(rb_cCeguiAnimationInstance,"maxStepDeltaClamp",1,1);


	rb_cCeguiAnimation = rb_define_class_under(rb_mCegui,"Animation",rb_cObject);
#endif
	using namespace CeguiAnimationInstance;

	rb_cCeguiAnimationInstance = rb_define_class_under(rb_cCeguiAnimation,"Instance",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiAnimationInstance);

	rb_define_attr_method(rb_cCeguiAnimationInstance,"target",_getTarget,_setTarget);
	rb_define_attr_method(rb_cCeguiAnimationInstance,"eventReceiver",_getEventReceiver,_setEventReceiver);
	rb_define_attr_method(rb_cCeguiAnimationInstance,"eventSender",_getEventSender,_setEventSender);

	rb_define_attr_method(rb_cCeguiAnimationInstance,"position",
		_getPosition,_setPosition);

	rb_define_attr_method(rb_cCeguiAnimationInstance,"speed",
		_getSpeed,_setSpeed);

	rb_define_attr_method(rb_cCeguiAnimationInstance,"skipNextStep",
		_getSkipNextStep,_setSkipNextStep);

	rb_define_attr_method(rb_cCeguiAnimationInstance,"maxStepDeltaSkip",
		_getMaxStepDeltaSkip,_setMaxStepDeltaSkip);

	rb_define_attr_method(rb_cCeguiAnimationInstance,"maxStepDeltaClamp",
		_getMaxStepDeltaClamp,_setMaxStepDeltaClamp);

	rb_define_method(rb_cCeguiAnimationInstance,"activate",RUBY_METHOD_FUNC(_stop),0);
	rb_define_method(rb_cCeguiAnimationInstance,"pause",RUBY_METHOD_FUNC(_pause),0);

	rb_define_method(rb_cCeguiAnimationInstance,"step",RUBY_METHOD_FUNC(_step),1);
//	rb_define_method(rb_cCeguiAnimationInstance,"deactivate",RUBY_METHOD_FUNC(_deactivate),0);

}
