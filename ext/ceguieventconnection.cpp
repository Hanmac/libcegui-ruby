#include "ceguieventconnection.hpp"
#include "ceguievent.hpp"
#include "ceguiexception.hpp"
#define _self wrap<CEGUI::Event::Connection>(self)

VALUE rb_cCeguiEventConnection;

namespace CeguiEventConnection {

singlereturn(connected)
singlefunc(disconnect)

}

/*Docoment-method: connected
*/
/*Docoment-method: disconnect
*/

void Init_CeguiEventConnection(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_cCeguiEvent = rb_define_class_under(rb_mCegui,"Event",rb_cObject);
#endif
	using namespace CeguiEventConnection;
	rb_cCeguiEventConnection = rb_define_class_under(rb_cCeguiEvent,"Connection",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiEventConnection);

	rb_define_method(rb_cCeguiEventConnection,"connected",RUBY_METHOD_FUNC(_connected),0);
	rb_define_method(rb_cCeguiEventConnection,"disconnect",RUBY_METHOD_FUNC(_disconnect),0);
}
