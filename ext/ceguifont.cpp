#include "ceguifont.hpp"
#include "ceguieventset.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Font*>(self)
#define _manager CEGUI::FontManager::getSingletonPtr()

VALUE rb_cCeguiFont;

/*
*/
VALUE CeguiFont_getName(VALUE self)
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
VALUE CeguiFont_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=CeguiFont_getName(self);
	return rb_f_sprintf(3,array);
}

/*
*/
VALUE CeguiFont_Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_manager->getIterator());
	return self;
}


/*
*/
VALUE CeguiFont_Manager_isDefined(VALUE self,VALUE name)
{
	return RBOOL(_manager->isDefined(wrap<CEGUI::String>(name)));
}
/*
*/
VALUE CeguiFont_Manager_get(VALUE self,VALUE name)
{
	CEGUI::String cname = wrap<CEGUI::String>(name);
	return _manager->isDefined(cname) ? wrap(&_manager->get(cname)) : Qnil;
}

/*
*/
VALUE CeguiFont_Manager_create(int argc,VALUE *argv,VALUE self)
{
	VALUE path,resource_group;
	rb_scan_args(argc, argv, "11",&path,&resource_group);
	try{
		return wrap(&_manager->create(wrap<CEGUI::String>(path),wrap<CEGUI::String>(resource_group)));
	}catch(CEGUI::Exception& e){
		rb_raise(wrap(e));
		return Qnil;
	}
}


/*
*/
VALUE CeguiFont_Manager_createAll(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,resource_group;
	rb_scan_args(argc, argv, "11",&pattern,&resource_group);
	_manager->createAll(wrap<CEGUI::String>(pattern),wrap<CEGUI::String>(resource_group));
	return self;
}
/*
*/
VALUE CeguiFont_Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::Font::getDefaultResourceGroup());
}
/*
*/
VALUE CeguiFont_Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::Font::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}



void Init_CeguiFont(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
#endif
	rb_cCeguiFont = rb_define_class_under(rb_mCegui,"Font",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiFont);

	rb_extend_object(rb_cCeguiFont,rb_mCeguiEventSet);
	rb_extend_object(rb_cCeguiFont,rb_mEnumerable);

	rb_define_method(rb_cCeguiFont,"name",RUBY_METHOD_FUNC(CeguiFont_getName),0);
	rb_define_method(rb_cCeguiFont,"inspect",RUBY_METHOD_FUNC(CeguiFont_inspect),0);

	rb_define_singleton_method(rb_cCeguiFont,"[]",RUBY_METHOD_FUNC(CeguiFont_Manager_get),1);
	rb_define_singleton_method(rb_cCeguiFont,"each",RUBY_METHOD_FUNC(CeguiFont_Manager_each),0);

	rb_define_singleton_method(rb_cCeguiFont,"defined?",RUBY_METHOD_FUNC(CeguiFont_Manager_isDefined),1);

	rb_define_singleton_method(rb_cCeguiFont,"create",RUBY_METHOD_FUNC(CeguiFont_Manager_create),-1);
	rb_define_singleton_method(rb_cCeguiFont,"createAll",RUBY_METHOD_FUNC(CeguiFont_Manager_createAll),-1);

	rb_define_singleton_method(rb_cCeguiFont,"defaultResourceGroup",RUBY_METHOD_FUNC(CeguiFont_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiFont,"defaultResourceGroup=",RUBY_METHOD_FUNC(CeguiFont_Manager_setDefaultResourceGroup),1);

}
