#include "ceguiresourceprovider.hpp"

#define _self wrap<CEGUI::ResourceProvider*>(self)

VALUE rb_cCeguiResourceProvider;

macro_attr(ResourceProvider,DefaultResourceGroup,CEGUI::String)

/*
*/
VALUE CeguiResourceProvider_getResourceGroupFileNames(VALUE self,VALUE file_pattern,VALUE resource_group)
{
	std::vector< CEGUI::String > out_vec;
	_self->getResourceGroupFileNames (out_vec,wrap<CEGUI::String>(file_pattern),wrap<CEGUI::String>(resource_group));
	return wrap(out_vec);
}
/*
*/
void Init_CeguiResourceProvider(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_define_attr(rb_cCeguiResourceProvider,"defaultResourceGroup",1,1);
#endif
	rb_cCeguiResourceProvider = rb_define_class_under(rb_mCegui,"ResourceProvider",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiResourceProvider);

	rb_define_attr_method(rb_cCeguiResourceProvider,"defaultResourceGroup",CeguiResourceProvider_getDefaultResourceGroup,CeguiResourceProvider_setDefaultResourceGroup);

	rb_define_method(rb_cCeguiResourceProvider,"filemames",RUBY_METHOD_FUNC(CeguiResourceProvider_getResourceGroupFileNames),2);
}
