#include "ceguiimage.hpp"
#include "ceguixmlserializer.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Image*>(self)
#define _manager CEGUI::ImageManager::getSingletonPtr()

VALUE rb_cCeguiImage;

/*
*/
VALUE CeguiImage_getName(VALUE self)
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
VALUE CeguiImage_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=CeguiImage_getName(self);
	return rb_f_sprintf(3,array);
}


/*
*/
VALUE CeguiImage_Manager_get(VALUE self,VALUE name)
{
	CEGUI::String cname = wrap<CEGUI::String>(name);
	return _manager->isDefined(cname) ? wrap(&_manager->get(cname)) : Qnil;
}

/*
*/
VALUE CeguiImage_Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::ImageManager::getImagesetDefaultResourceGroup());
}
/*
*/
VALUE CeguiImage_Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}
/*
*/
VALUE CeguiImage_Manager_loadImageset(int argc,VALUE *argv,VALUE self)
{
	VALUE filename,resourceGroup;
	rb_scan_args(argc, argv, "11",&filename,&resourceGroup);
	try{
		_manager->loadImageset(wrap<CEGUI::String>(filename),wrap<CEGUI::String>(resourceGroup));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
	return self;
}
/*
*/
VALUE CeguiImage_Manager_count(VALUE self)
{
	return ULONG2NUM(_manager->getImageCount());
}
/*
*/
void Init_CeguiImage(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiImage = rb_define_class_under(rb_mCegui,"Image",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiImage);

	rb_define_method(rb_cCeguiImage,"name",RUBY_METHOD_FUNC(CeguiImage_getName),0);
	rb_define_method(rb_cCeguiImage,"inspect",RUBY_METHOD_FUNC(CeguiImage_inspect),0);

	rb_define_singleton_method(rb_cCeguiImage,"[]",RUBY_METHOD_FUNC(CeguiImage_Manager_get),1);
	rb_define_singleton_method(rb_cCeguiImage,"loadImageset",
		RUBY_METHOD_FUNC(CeguiImage_Manager_loadImageset),-1);
	rb_define_singleton_method(rb_cCeguiImage,"count",RUBY_METHOD_FUNC(CeguiImage_Manager_count),0);

	rb_define_singleton_method(rb_cCeguiImage,"defaultResourceGroup",RUBY_METHOD_FUNC(CeguiImage_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiImage,"defaultResourceGroup=",RUBY_METHOD_FUNC(CeguiImage_Manager_setDefaultResourceGroup),1);
}
