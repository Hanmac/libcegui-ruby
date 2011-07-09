#include "ceguieventconnection.hpp"
#include "ceguievent.hpp"
#define _self wrap<CEGUI::Event::Connection>(self)

VALUE rb_cCeguiEventConnection;

/*
*/
VALUE CeguiEventConnection_connected(VALUE self)
{
	return RBOOL(_self->connected());
}

/*
*/
VALUE CeguiEventConnection_disconnect(VALUE self)
{
	_self->disconnect();
	return Qnil;
}


void Init_CeguiEventConnection(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_cCeguiEvent = rb_define_class_under(rb_mCegui,"Event",rb_cObject);
#endif
	rb_cCeguiEventConnection = rb_define_class_under(rb_cCeguiEvent,"Connection",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiEventConnection);

	rb_define_method(rb_cCeguiEventConnection,"connected",RUBY_METHOD_FUNC(CeguiEventConnection_connected),0);
	rb_define_method(rb_cCeguiEventConnection,"disconnect",RUBY_METHOD_FUNC(CeguiEventConnection_disconnect),0);
}
