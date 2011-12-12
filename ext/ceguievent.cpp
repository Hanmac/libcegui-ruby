#include "ceguievent.hpp"
#include "ceguieventargs.hpp"
#include "ceguiexception.hpp"
#include <iostream>
#define _self wrap<CEGUI::Event*>(self)
VALUE rb_cCeguiEvent,subscriberholder;

	Subscriberfunc::Subscriberfunc(VALUE val) : value(val){
		rb_ary_push(subscriberholder,val);//TODO find a way to GC them
	};
	bool Subscriberfunc::operator()(const CEGUI::EventArgs& e){
		if(NUM2INT(rb_funcall(value,rb_intern("arity"),0)) == 0)
			return RTEST(rb_funcall(value,rb_intern("call"),0));
		else
			return RTEST(rb_funcall(value,rb_intern("call"),1,wrap(&e)));
	}
	Subscriberfunc::~Subscriberfunc(){
		std::cout << "FREE" << std::endl;
	}

/*
*/
VALUE CeguiEvent_getName(VALUE self)
{
	return wrap(_self->getName());
}
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiEvent_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=CeguiEvent_getName(self);
	return rb_f_sprintf(3,array);
}

/*
*/
VALUE CeguiEvent_call(VALUE self,VALUE vargs)
{
	CEGUI::EventArgs args = wrap<CEGUI::EventArgs>(vargs);
	(*wrap<CEGUI::Event*>(self))(args);
	return self;
}
/*
*/
VALUE CeguiEvent_subscribe(int argc,VALUE *argv,VALUE self)
{
	VALUE subscriber_name;
	rb_scan_args(argc, argv, "01",&subscriber_name);
	try{
		if(NIL_P(subscriber_name)){
			return wrap(_self->subscribe(new Subscriberfunc(rb_block_proc())));
		}else
			return wrap(_self->subscribe(new Subscriberfunc(subscriber_name)));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;

}
void Init_CeguiEvent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif
	rb_cCeguiEvent = rb_define_class_under(rb_mCegui,"Event",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiEvent);
	
	rb_define_method(rb_cCeguiEvent,"inspect",RUBY_METHOD_FUNC(CeguiEvent_inspect),0);
	rb_define_method(rb_cCeguiEvent,"name",RUBY_METHOD_FUNC(CeguiEvent_getName),0);
	rb_define_method(rb_cCeguiEvent,"call",RUBY_METHOD_FUNC(CeguiEvent_call),1);
	rb_define_alias(rb_cCeguiEvent,"[]","call");

	rb_define_method(rb_cCeguiEvent,"subscribe",RUBY_METHOD_FUNC(CeguiEvent_subscribe),0);
	
	subscriberholder = rb_ary_new();
	rb_global_variable(&subscriberholder);
}
