#include "ceguiresourceprovider.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::ResourceProvider*>(self)

VALUE rb_cCeguiResourceProvider;
namespace CeguiResourceProvider {

macro_attr(DefaultResourceGroup,CEGUI::String)

/*
*/
VALUE _getResourceGroupFileNames(VALUE self,VALUE file_pattern,VALUE resource_group)
{
	std::vector< CEGUI::String > out_vec;
	_self->getResourceGroupFileNames (out_vec,wrap<CEGUI::String>(file_pattern),wrap<CEGUI::String>(resource_group));
	return wrap(out_vec);
}

}
/*
*/
void Init_CeguiResourceProvider(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiResourceProvider,"defaultResourceGroup",1,1);
#endif
	using namespace CeguiResourceProvider;

	rb_cCeguiResourceProvider = rb_define_class_under(rb_mCegui,"ResourceProvider",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiResourceProvider);

	rb_define_attr_method(rb_cCeguiResourceProvider,"defaultResourceGroup",_getDefaultResourceGroup,_setDefaultResourceGroup);

	rb_define_method(rb_cCeguiResourceProvider,"filemames",RUBY_METHOD_FUNC(_getResourceGroupFileNames),2);
}
