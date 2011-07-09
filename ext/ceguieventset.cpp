#include "ceguieventset.hpp"
#include "ceguievent.hpp"
#include "ceguieventconnection.hpp"
#include "ceguieventargs.hpp"
#define _self wrap<CEGUI::EventSet*>(self)
VALUE rb_mCeguiEventSet;
/*
*/
VALUE CeguiEventSet_each_event(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getIterator());//EventSet::
	return self;
}

/*
*/
VALUE CeguiEventSet_subscribe(int argc,VALUE *argv,VALUE self)
{
	VALUE name,subscriber_name;
	rb_scan_args(argc, argv, "11",&name,&subscriber_name);
	if(NIL_P(subscriber_name))
		return wrap(_self->subscribeEvent(wrap<CEGUI::String>(name),CEGUI::SubscriberSlot(Subscriberfunc(rb_block_proc()))));
	else
		return wrap(_self->subscribeScriptedEvent(wrap<CEGUI::String>(name),wrap<CEGUI::String>(subscriber_name)));
}

/*
*/
VALUE CeguiEventSet_fireEvent(int argc,VALUE *argv,VALUE self)
{
	VALUE name,vargs,eventNamespace;
	rb_scan_args(argc, argv, "21",&name,&vargs,&eventNamespace);
	CEGUI::EventArgs args = wrap<CEGUI::EventArgs>(vargs);
	_self->fireEvent(wrap<CEGUI::String>(name), args, wrap<CEGUI::String>(eventNamespace));
	return self;
}
/*
*/
VALUE CeguiEventSet_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE methID,arg;
	rb_scan_args(argc, argv, "1*",&methID,&arg);
	methID = rb_funcall(methID,rb_intern("to_s"),0);
	return rb_call_super(argc,argv);
}


void Init_CeguiEventSet(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
#endif
	rb_mCeguiEventSet = rb_define_module_under(rb_mCegui,"EventSet");

	rb_define_method(rb_mCeguiEventSet,"each_event",RUBY_METHOD_FUNC(CeguiEventSet_each_event),0);
	
	rb_define_method(rb_mCeguiEventSet,"subscribe",RUBY_METHOD_FUNC(CeguiEventSet_subscribe),-1);
	rb_define_method(rb_mCeguiEventSet,"fireEvent",RUBY_METHOD_FUNC(CeguiEventSet_fireEvent),-1);

	rb_define_method(rb_mCeguiEventSet,"method_missing",RUBY_METHOD_FUNC(CeguiEventSet_method_missing),-1);
}
