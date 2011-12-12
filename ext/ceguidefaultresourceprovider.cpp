#include "ceguiresourceprovider.hpp"
#include "ceguidefaultresourceprovider.hpp"

#define _self wrap<CEGUI::DefaultResourceProvider*>(self)

VALUE rb_cCeguiDefaultResourceProvider;

VALUE CeguiDefaultResourceProvider_alloc(VALUE self)
{
	return wrap(new CEGUI::DefaultResourceProvider);
}


/*
*/
VALUE CeguiDefaultResourceProvider_get(VALUE self,VALUE name)
{
	return wrap(_self->getResourceGroupDirectory(wrap<CEGUI::String>(name)));
}
/*
*/
VALUE CeguiDefaultResourceProvider_set(VALUE self,VALUE name,VALUE path)
{
	_self->setResourceGroupDirectory(wrap<CEGUI::String>(name),wrap<CEGUI::String>(path));
	return path;
}
/*
*/
void Init_CeguiDefaultResourceProvider(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_cCeguiResourceProvider = rb_define_class_under(rb_mCegui,"ResourceProvider",rb_cObject);
#endif
	rb_cCeguiDefaultResourceProvider = rb_define_class_under(rb_mCegui,"DefaultResourceProvider",rb_cCeguiResourceProvider);
	
	rb_define_alloc_func(rb_cCeguiDefaultResourceProvider,CeguiDefaultResourceProvider_alloc);

	rb_define_method(rb_cCeguiDefaultResourceProvider,"[]",RUBY_METHOD_FUNC(CeguiDefaultResourceProvider_get),1);
	rb_define_method(rb_cCeguiDefaultResourceProvider,"[]=",RUBY_METHOD_FUNC(CeguiDefaultResourceProvider_set),2);
}
