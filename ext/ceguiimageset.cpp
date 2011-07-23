#include "ceguiimageset.hpp"
#include "ceguieventset.hpp"
#include "ceguiexception.hpp"

#include "ceguixmlserializer.hpp"

#include "ceguiimage.hpp"

#define _self wrap<CEGUI::Imageset*>(self)
#define _manager CEGUI::ImagesetManager::getSingletonPtr()

VALUE rb_cCeguiImageset;

macro_attr(Imageset,NativeResolution,CEGUI::Size)
/*
*/
VALUE CeguiImageset_getName(VALUE self)
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
VALUE CeguiImageset_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=CeguiImageset_getName(self);
	return rb_f_sprintf(3,array);
}

/*
*/
VALUE CeguiImageset_each(VALUE self)
{
	wrap_each(_self->getIterator());
	return self;
}
/*
*/
VALUE CeguiImageset_writeXML(VALUE self,VALUE xml)
{
	CEGUI::XMLSerializer *temp =wrap<CEGUI::XMLSerializer*>(xml);
	_self->writeXMLToStream(*temp);
	return self;
}

/*
*/
VALUE CeguiImageset_Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_manager->getIterator());
	return self;
}


/*
*/
VALUE CeguiImageset_Manager_isDefined(VALUE self,VALUE name)
{
	return RBOOL(_manager->isDefined(wrap<CEGUI::String>(name)));
}
/*
*/
VALUE CeguiImageset_Manager_get(VALUE self,VALUE name)
{
	CEGUI::String cname = wrap<CEGUI::String>(name);
	return _manager->isDefined(cname) ? wrap(_manager->get(cname)) : Qnil;
}

/*
*/
VALUE CeguiImageset_Manager_create(int argc,VALUE *argv,VALUE self)
{
	VALUE path,resource_group;
	rb_scan_args(argc, argv, "11",&path,&resource_group);
	try{
		return wrap(_manager->create(wrap<CEGUI::String>(path),wrap<CEGUI::String>(resource_group)));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}


/*
*/
VALUE CeguiImageset_Manager_createAll(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,resource_group;
	rb_scan_args(argc, argv, "11",&pattern,&resource_group);
	_manager->createAll(wrap<CEGUI::String>(pattern),wrap<CEGUI::String>(resource_group));
	return self;
}
/*
*/
VALUE CeguiImageset_Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::Imageset::getDefaultResourceGroup());
}
/*
*/
VALUE CeguiImageset_Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::Imageset::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}

/*
*/
void Init_CeguiImageset(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiImageset,"nativeResolution",1,1);
	
#endif
	rb_cCeguiImageset = rb_define_class_under(rb_mCegui,"Imageset",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiImageset);

	rb_extend_object(rb_cCeguiImageset,rb_mCeguiEventSet);
	rb_extend_object(rb_cCeguiImageset,rb_mEnumerable);
	
	rb_include_module(rb_cCeguiImageset,rb_mEnumerable);

	rb_define_method(rb_cCeguiImageset,"name",RUBY_METHOD_FUNC(CeguiImageset_getName),0);
	rb_define_method(rb_cCeguiImageset,"inspect",RUBY_METHOD_FUNC(CeguiImageset_inspect),0);

	rb_define_attr_method(rb_cCeguiImageset,"nativeResolution",CeguiImageset_getNativeResolution,CeguiImageset_setNativeResolution);

	rb_define_method(rb_cCeguiImageset,"each",RUBY_METHOD_FUNC(CeguiImageset_each),0);

	rb_define_method(rb_cCeguiImageset,"writeXML",RUBY_METHOD_FUNC(CeguiImageset_writeXML),1);

	rb_define_singleton_method(rb_cCeguiImageset,"[]",RUBY_METHOD_FUNC(CeguiImageset_Manager_get),1);
	rb_define_singleton_method(rb_cCeguiImageset,"each",RUBY_METHOD_FUNC(CeguiImageset_Manager_each),0);

	rb_define_singleton_method(rb_cCeguiImageset,"defined?",RUBY_METHOD_FUNC(CeguiImageset_Manager_isDefined),1);

	rb_define_singleton_method(rb_cCeguiImageset,"create",RUBY_METHOD_FUNC(CeguiImageset_Manager_create),-1);
	rb_define_singleton_method(rb_cCeguiImageset,"createAll",RUBY_METHOD_FUNC(CeguiImageset_Manager_createAll),-1);

	rb_define_singleton_method(rb_cCeguiImageset,"defaultResourceGroup",RUBY_METHOD_FUNC(CeguiImageset_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiImageset,"defaultResourceGroup=",RUBY_METHOD_FUNC(CeguiImageset_Manager_setDefaultResourceGroup),1);

}
