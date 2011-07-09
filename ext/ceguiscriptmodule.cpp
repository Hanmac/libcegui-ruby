#include "ceguiscriptmodule.hpp"
#include "ceguiexception.hpp"


#define _self wrap<CEGUI::ScriptModule*>(self)

VALUE rb_cCeguiScriptModule;

/*
*/
VALUE CeguiScriptModule_getName(VALUE self)
{
	return wrap(_self->getIdentifierString());
}

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiScriptModule_inspect(VALUE self)
{
	VALUE array[2];
	array[0]=rb_str_new2("#<%s>");
	array[1]=CeguiScriptModule_getName(self);
	return rb_f_sprintf(2,array);
}


/*
*/
VALUE CeguiScriptModule_Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::ScriptModule::getDefaultResourceGroup());
}
/*
*/
VALUE CeguiScriptModule_Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::ScriptModule::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}


void Init_CeguiScriptModule(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiScriptModule = rb_define_class_under(rb_mCegui,"ScriptModule",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiScriptModule);

	rb_define_method(rb_cCeguiScriptModule,"name",RUBY_METHOD_FUNC(CeguiScriptModule_getName),0);
	rb_define_method(rb_cCeguiScriptModule,"inspect",RUBY_METHOD_FUNC(CeguiScriptModule_inspect),0);

	rb_define_singleton_method(rb_cCeguiScriptModule,"defaultResourceGroup",RUBY_METHOD_FUNC(CeguiScriptModule_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiScriptModule,"defaultResourceGroup=",RUBY_METHOD_FUNC(CeguiScriptModule_Manager_setDefaultResourceGroup),1);

}
