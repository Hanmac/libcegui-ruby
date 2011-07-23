#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Thumb*>(self)
VALUE rb_cCeguiThumb;

/*
*/
VALUE CeguiThumb_new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::Thumb::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

VALUE CeguiThumb_setHotTracked(VALUE self,VALUE val)
{
	_self->setHotTracked(RTEST(val));
	return val;
}

VALUE CeguiThumb_setVertFree(VALUE self,VALUE val)
{
	_self->setVertFree(RTEST(val));
	return val;
}

VALUE CeguiThumb_setHorzFree(VALUE self,VALUE val)
{
	_self->setHorzFree(RTEST(val));
	return val;
}

VALUE CeguiThumb_getHotTracked(VALUE self)
{
	return RBOOL(_self->isHotTracked());
}
VALUE CeguiThumb_getVertFree(VALUE self)
{
	return RBOOL(_self->isVertFree());
}
VALUE CeguiThumb_getHorzFree(VALUE self)
{
	return RBOOL(_self->isHorzFree());
}

VALUE CeguiThumb_getVertRange(VALUE self)
{
	return wrap(_self->getVertRange());
}

VALUE CeguiThumb_getHorzRange(VALUE self)
{
	return wrap(_self->getHorzRange());
}


VALUE CeguiThumb_setVertRange(VALUE self,VALUE val)
{
	VALUE b= rb_funcall(val,rb_intern("begin"),0);
	VALUE e= rb_funcall(val,rb_intern("end"),0);
	_self->setVertRange(NUM2DBL(b),NUM2DBL(e));
	return val;
}

VALUE CeguiThumb_setHorzRange(VALUE self,VALUE val)
{
	VALUE b= rb_funcall(val,rb_intern("begin"),0);
	VALUE e= rb_funcall(val,rb_intern("end"),0);
	_self->setHorzRange(NUM2DBL(b),NUM2DBL(e));
	return val;
}

/*
*/
void Init_CeguiThumb(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiButtonBase = rb_define_class_under(rb_mCegui,"ButtonBase",rb_cCeguiWindow);
	rb_cCeguiPushButton = rb_define_class_under(rb_mCegui,"PushButton",rb_cCeguiButtonBase);
	
	rb_define_attr(rb_cCeguiThumb,"hotTracked",1,1);
	rb_define_attr(rb_cCeguiThumb,"vertFree",1,1);
	rb_define_attr(rb_cCeguiThumb,"horzFree",1,1);
#endif

	rb_cCeguiThumb = rb_define_class_under(rb_mCegui,"Thumb",rb_cCeguiPushButton);

	rb_define_attr_method(rb_cCeguiThumb,"hotTracked",CeguiThumb_getHotTracked,CeguiThumb_setHotTracked);
	rb_define_attr_method(rb_cCeguiThumb,"vertFree",CeguiThumb_getVertFree,CeguiThumb_setVertFree);
	rb_define_attr_method(rb_cCeguiThumb,"horzFree",CeguiThumb_getHorzFree,CeguiThumb_setHorzFree);

	rb_define_attr_method(rb_cCeguiThumb,"vertRange",CeguiThumb_getVertRange,CeguiThumb_setVertRange);
	rb_define_attr_method(rb_cCeguiThumb,"horzRange",CeguiThumb_getHorzRange,CeguiThumb_setHorzRange);

	
	rb_define_singleton_method(rb_cCeguiThumb,"new",RUBY_METHOD_FUNC(CeguiThumb_new),-1);

	rb_define_const(rb_cCeguiThumb,"WidgetTypeName",wrap(CEGUI::Thumb::WidgetTypeName));
	rb_define_const(rb_cCeguiThumb,"EventNamespace",wrap(CEGUI::Thumb::EventNamespace));
	
	
	rb_define_const(rb_cCeguiThumb,"EventThumbPositionChanged",wrap(CEGUI::Thumb::EventThumbPositionChanged));
	rb_define_const(rb_cCeguiThumb,"EventThumbTrackStarted",wrap(CEGUI::Thumb::EventThumbTrackStarted));
	rb_define_const(rb_cCeguiThumb,"EventThumbTrackEnded",wrap(CEGUI::Thumb::EventThumbTrackEnded));
}
