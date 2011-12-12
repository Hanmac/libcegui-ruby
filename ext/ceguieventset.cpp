#include "ceguieventset.hpp"
#include "ceguievent.hpp"
#include "ceguieventconnection.hpp"
#include "ceguieventargs.hpp"


#include "ceguiexception.hpp"


#define _self wrap<CEGUI::EventSet*>(self)
VALUE rb_mCeguiEventSet;

std::map<VALUE,CEGUI::EventSet*> eventsetholder;

/*
*/
VALUE CeguiEventSet_each_event(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getEventIterator());//EventSet::
	return self;
}
/*
*/
VALUE CeguiEventSet_addEvent(VALUE self,VALUE name)
{
	try{
		_self->addEvent(wrap<CEGUI::String>(name));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}
/*
*/
VALUE CeguiEventSet_removeEvent(VALUE self,VALUE name)
{
	try{
		_self->removeEvent(wrap<CEGUI::String>(name));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}
/*
*/
VALUE CeguiEventSet_subscribe(int argc,VALUE *argv,VALUE self)
{
	VALUE name,subscriber_name;
	rb_scan_args(argc, argv, "11",&name,&subscriber_name);
	try{
		if(NIL_P(subscriber_name)){
			VALUE val = rb_block_proc();
//		rb_global_variable(&val);
			return wrap(_self->subscribeEvent(wrap<CEGUI::String>(name),new Subscriberfunc(val)));
		}else if(rb_obj_is_kind_of(subscriber_name,rb_cMethod)){
			return wrap(_self->subscribeEvent(wrap<CEGUI::String>(name),new Subscriberfunc(subscriber_name)));
		}else
			return wrap(_self->subscribeScriptedEvent(wrap<CEGUI::String>(name),
				wrap<CEGUI::String>(subscriber_name)));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}

/*
*/
VALUE CeguiEventSet_fireEvent(int argc,VALUE *argv,VALUE self)
{
	VALUE name,vargs,eventNamespace;
	rb_scan_args(argc, argv, "21",&name,&vargs,&eventNamespace);
	CEGUI::EventArgs *args = wrap<CEGUI::EventArgs*>(vargs);
	_self->fireEvent(wrap<CEGUI::String>(name), *args, wrap<CEGUI::String>(eventNamespace));
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
	rb_mCegui = rb_define_module("CEGUI");
#endif
	rb_mCeguiEventSet = rb_define_module_under(rb_mCegui,"EventSet");

	rb_define_method(rb_mCeguiEventSet,"each_event",RUBY_METHOD_FUNC(CeguiEventSet_each_event),0);
	
	rb_define_method(rb_mCeguiEventSet,"add_event",RUBY_METHOD_FUNC(CeguiEventSet_addEvent),1);
	rb_define_method(rb_mCeguiEventSet,"remove_event",RUBY_METHOD_FUNC(CeguiEventSet_removeEvent),1);
	//rb_define_method(rb_mCeguiEventSet,"hasEvent?",RUBY_METHOD_FUNC(CeguiEventSet_isEventPresent),1);
	
	rb_define_method(rb_mCeguiEventSet,"subscribe",RUBY_METHOD_FUNC(CeguiEventSet_subscribe),-1);
	rb_define_method(rb_mCeguiEventSet,"fireEvent",RUBY_METHOD_FUNC(CeguiEventSet_fireEvent),-1);

	//rb_define_method(rb_mCeguiEventSet,"method_missing",RUBY_METHOD_FUNC(CeguiEventSet_method_missing),-1);
}
