#include "ceguievent.hpp"
#include "ceguieventargs.hpp"
#define _self wrap<CEGUI::Event*>(self)
VALUE rb_cCeguiEvent,subscriberholder;

	Subscriberfunc::Subscriberfunc(VALUE val) : value(val){
		rb_ary_push(subscriberholder,val);//TODO find a way to GC them
	};
	bool Subscriberfunc::operator()(const CEGUI::EventArgs& e){
		return RTEST(rb_funcall(value,rb_intern("call"),1,wrap(e)));
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
VALUE CeguiEvent_subscribe(VALUE self)
{
	return wrap(_self->subscribe(CEGUI::SubscriberSlot(Subscriberfunc(rb_block_proc()))));
}
void Init_CeguiEvent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
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
