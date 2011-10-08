#include "ceguischeme.hpp"
#include "ceguieventset.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Scheme*>(self)
#define _manager CEGUI::SchemeManager::getSingletonPtr()

VALUE rb_cCeguiScheme;

/*
*/
VALUE CeguiScheme_getName(VALUE self)
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
VALUE CeguiScheme_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=CeguiScheme_getName(self);
	return rb_f_sprintf(3,array);
}

/*
*/
VALUE CeguiScheme_loadResources(VALUE self)
{
	try{
		_self->loadResources();
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
	return self;
}


/*
*/
VALUE CeguiScheme_resourcesLoaded(VALUE self)
{
	return RBOOL(_self->resourcesLoaded());
}
/*
*/
VALUE CeguiScheme_Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_manager->getIterator());
	return self;
}


/*
*/
VALUE CeguiScheme_Manager_isDefined(VALUE self,VALUE name)
{
	return RBOOL(_manager->isDefined(wrap<CEGUI::String>(name)));
}
/*
*/
VALUE CeguiScheme_Manager_get(VALUE self,VALUE name)
{
	CEGUI::String cname = wrap<CEGUI::String>(name);
	return _manager->isDefined(cname) ? wrap(_manager->get(cname)) : Qnil;
}

/*
*/
VALUE CeguiScheme_Manager_create(int argc,VALUE *argv,VALUE self)
{
	VALUE path,resource_group;
	rb_scan_args(argc, argv, "11",&path,&resource_group);
	try{
		return wrap(_manager->createFromFile(wrap<CEGUI::String>(path),wrap<CEGUI::String>(resource_group)));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}


/*
*/
VALUE CeguiScheme_Manager_createAll(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,resource_group;
	rb_scan_args(argc, argv, "11",&pattern,&resource_group);
	try{
		_manager->createAll(wrap<CEGUI::String>(pattern),wrap<CEGUI::String>(resource_group));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
	return self;
}
/*
*/
VALUE CeguiScheme_Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::Scheme::getDefaultResourceGroup());
}
/*
*/
VALUE CeguiScheme_Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::Scheme::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}



void Init_CeguiScheme(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiScheme = rb_define_class_under(rb_mCegui,"Scheme",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiScheme);

	rb_extend_object(rb_cCeguiScheme,rb_mCeguiEventSet);
	rb_extend_object(rb_cCeguiScheme,rb_mEnumerable);

	rb_define_method(rb_cCeguiScheme,"name",RUBY_METHOD_FUNC(CeguiScheme_getName),0);
	rb_define_method(rb_cCeguiScheme,"inspect",RUBY_METHOD_FUNC(CeguiScheme_inspect),0);


	rb_define_method(rb_cCeguiScheme,"load",RUBY_METHOD_FUNC(CeguiScheme_loadResources),0);
	rb_define_method(rb_cCeguiScheme,"loaded?",RUBY_METHOD_FUNC(CeguiScheme_resourcesLoaded),0);


	rb_define_singleton_method(rb_cCeguiScheme,"[]",RUBY_METHOD_FUNC(CeguiScheme_Manager_get),1);
	rb_define_singleton_method(rb_cCeguiScheme,"each",RUBY_METHOD_FUNC(CeguiScheme_Manager_each),0);

	rb_define_singleton_method(rb_cCeguiScheme,"defined?",RUBY_METHOD_FUNC(CeguiScheme_Manager_isDefined),1);

	rb_define_singleton_method(rb_cCeguiScheme,"create",RUBY_METHOD_FUNC(CeguiScheme_Manager_create),-1);
	rb_define_singleton_method(rb_cCeguiScheme,"createAll",RUBY_METHOD_FUNC(CeguiScheme_Manager_createAll),-1);

	rb_define_singleton_method(rb_cCeguiScheme,"defaultResourceGroup",RUBY_METHOD_FUNC(CeguiScheme_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiScheme,"defaultResourceGroup=",RUBY_METHOD_FUNC(CeguiScheme_Manager_setDefaultResourceGroup),1);

}
