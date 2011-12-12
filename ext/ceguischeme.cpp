#include "ceguischeme.hpp"
#include "ceguieventset.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Scheme*>(self)
#define _manager CEGUI::SchemeManager::getSingletonPtr()

VALUE rb_cCeguiScheme;

namespace CeguiScheme {
/*
*/
VALUE _getName(VALUE self)
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
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=_getName(self);
	return rb_f_sprintf(3,array);
}

singlefunc(loadResources)
singlefunc(loadXMLImagesets)
singlefunc(loadImageFileImagesets)
singlefunc(loadFonts)
singlefunc(loadLookNFeels)
singlefunc(loadWindowFactories)
singlefunc(loadWindowRendererFactories)
singlefunc(loadFactoryAliases)
singlefunc(loadFalagardMappings)

singlefunc(unloadResources)
singlefunc(unloadXMLImagesets)
singlefunc(unloadImageFileImagesets)
singlefunc(unloadFonts)
singlefunc(unloadLookNFeels)
singlefunc(unloadWindowFactories)
singlefunc(unloadWindowRendererFactories)
singlefunc(unloadFactoryAliases)
singlefunc(unloadFalagardMappings)



/*
*/
VALUE _resourcesLoaded(VALUE self)
{
	return RBOOL(_self->resourcesLoaded());
}
/*
*/
VALUE _each_XMLImagesets(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getXMLImagesets());
	return self;
}
/*
*/
VALUE _each_ImageFileImagesets(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getImageFileImagesets());
	return self;
}
/*
*/
VALUE _each_Fonts(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getFonts());
	return self;
}
/*
*/
VALUE _each_LookNFeels(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getLookNFeels());
	return self;
}

/*
*/
VALUE _Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_manager->getIterator());
	return self;
}


/*
*/
VALUE _Manager_isDefined(VALUE self,VALUE name)
{
	return RBOOL(_manager->isDefined(wrap<CEGUI::String>(name)));
}
/*
*/
VALUE _Manager_get(VALUE self,VALUE name)
{
	CEGUI::String cname = wrap<CEGUI::String>(name);
	return _manager->isDefined(cname) ? wrap(_manager->get(cname)) : Qnil;
}

/*
*/
VALUE _Manager_create(int argc,VALUE *argv,VALUE self)
{
	VALUE path,resource_group;
	rb_scan_args(argc, argv, "11",&path,&resource_group);
	try{
		VALUE result = wrap(_manager->createFromFile(wrap<CEGUI::String>(path),wrap<CEGUI::String>(resource_group)));
		rb_funcall2(result,rb_intern("initialize"),argc,argv);
		return result;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}


/*
*/
VALUE _Manager_createAll(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,resource_group;
	rb_scan_args(argc, argv, "11",&pattern,&resource_group);
	try{
		_manager->createAll(wrap<CEGUI::String>(pattern),wrap<CEGUI::String>(resource_group));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}
/*
*/
VALUE _Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::Scheme::getDefaultResourceGroup());
}
/*
*/
VALUE _Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::Scheme::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}

/*
*/
VALUE _areXMLImagesetsLoaded(VALUE self)
{
	return wrap(_self->areXMLImagesetsLoaded());
}
/*
*/
VALUE _areFontsLoaded(VALUE self)
{
	return wrap(_self->areFontsLoaded());
}
/*
*/
VALUE _areImageFileImagesetsLoaded(VALUE self)
{
	return wrap(_self->areImageFileImagesetsLoaded());
}/*
*/
VALUE _areLookNFeelsLoaded(VALUE self)
{
	return wrap(_self->areLookNFeelsLoaded());
}
/*
*/
VALUE _areWindowFactoriesLoaded(VALUE self)
{
	return wrap(_self->areWindowFactoriesLoaded());
}
/*
*/
VALUE _areWindowRendererFactoriesLoaded(VALUE self)
{
	return wrap(_self->areWindowRendererFactoriesLoaded());
}
/*
*/
VALUE _areFactoryAliasesLoaded(VALUE self)
{
	return wrap(_self->areFactoryAliasesLoaded());
}
/*
*/
VALUE _areFalagardMappingsLoaded(VALUE self)
{
	return wrap(_self->areFalagardMappingsLoaded());
}


}

/* Document-method: load 

*/
/* Document-method: loadXMLImagesets 

*/
/* Document-method: loadImageFileImagesets 

*/
/* Document-method: loadFonts 

*/
/* Document-method: loadLookNFeels 

*/
/* Document-method: loadWindowFactories 

*/
/* Document-method: loadWindowRendererFactories 

*/
/* Document-method: loadFactoryAliases 

*/
/* Document-method: loadFalagardMappings 

*/
/* Document-method: unload 

*/
/* Document-method: unloadXMLImagesets 

*/
/* Document-method: unloadImageFileImagesets 

*/
/* Document-method: unloadFonts 

*/
/* Document-method: unloadLookNFeels 

*/
/* Document-method: unloadWindowFactories 

*/
/* Document-method: unloadWindowRendererFactories 

*/
/* Document-method: unloadFactoryAliases 

*/
/* Document-method: unloadFalagardMappings 

*/

void Init_CeguiScheme(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
#endif

	using namespace CeguiScheme;
	rb_cCeguiScheme = rb_define_class_under(rb_mCegui,"Scheme",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiScheme);

	rb_define_method(rb_cCeguiScheme,"initialize",RUBY_METHOD_FUNC(Cegui_dummy1),1);

	rb_extend_object(rb_cCeguiScheme,rb_mCeguiEventSet);
	rb_extend_object(rb_cCeguiScheme,rb_mEnumerable);

	rb_define_method(rb_cCeguiScheme,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cCeguiScheme,"inspect",RUBY_METHOD_FUNC(_inspect),0);


	rb_define_method(rb_cCeguiScheme,"load",RUBY_METHOD_FUNC(_loadResources),0);
	
	rb_define_method(rb_cCeguiScheme,"loaded?",RUBY_METHOD_FUNC(_resourcesLoaded),0);

	rb_define_method(rb_cCeguiScheme,"loadXMLImagesets",RUBY_METHOD_FUNC(_loadXMLImagesets),0);
	rb_define_method(rb_cCeguiScheme,"loadImageFileImagesets",RUBY_METHOD_FUNC(_loadImageFileImagesets),0);
	rb_define_method(rb_cCeguiScheme,"loadFonts",RUBY_METHOD_FUNC(_loadFonts),0);
	rb_define_method(rb_cCeguiScheme,"loadLookNFeels",RUBY_METHOD_FUNC(_loadLookNFeels),0);
	rb_define_method(rb_cCeguiScheme,"loadWindowFactories",RUBY_METHOD_FUNC(_loadWindowFactories),0);
	rb_define_method(rb_cCeguiScheme,"loadWindowRendererFactories",RUBY_METHOD_FUNC(_loadWindowRendererFactories),0);
	rb_define_method(rb_cCeguiScheme,"loadFactoryAliases",RUBY_METHOD_FUNC(_loadFactoryAliases),0);
	rb_define_method(rb_cCeguiScheme,"loadFalagardMappings",RUBY_METHOD_FUNC(_loadFalagardMappings),0);

	rb_define_method(rb_cCeguiScheme,"unload",RUBY_METHOD_FUNC(_unloadResources),0);

	rb_define_method(rb_cCeguiScheme,"unloadXMLImagesets",RUBY_METHOD_FUNC(_unloadXMLImagesets),0);
	rb_define_method(rb_cCeguiScheme,"unloadImageFileImagesets",RUBY_METHOD_FUNC(_unloadImageFileImagesets),0);
	rb_define_method(rb_cCeguiScheme,"unloadFonts",RUBY_METHOD_FUNC(_unloadFonts),0);
	rb_define_method(rb_cCeguiScheme,"unloadLookNFeels",RUBY_METHOD_FUNC(_unloadLookNFeels),0);
	rb_define_method(rb_cCeguiScheme,"unloadWindowFactories",RUBY_METHOD_FUNC(_unloadWindowFactories),0);
	rb_define_method(rb_cCeguiScheme,"unloadWindowRendererFactories",RUBY_METHOD_FUNC(_unloadWindowRendererFactories),0);
	rb_define_method(rb_cCeguiScheme,"unloadFactoryAliases",RUBY_METHOD_FUNC(_unloadFactoryAliases),0);
	rb_define_method(rb_cCeguiScheme,"unloadFalagardMappings",RUBY_METHOD_FUNC(_unloadFalagardMappings),0);

	rb_define_method(rb_cCeguiScheme,"XMLImagesets_loaded?",RUBY_METHOD_FUNC(_areXMLImagesetsLoaded),0);
	rb_define_method(rb_cCeguiScheme,"ImageFileImagesets_loaded?",RUBY_METHOD_FUNC(_areImageFileImagesetsLoaded),0);
	rb_define_method(rb_cCeguiScheme,"Fonts_loaded?",RUBY_METHOD_FUNC(_areFontsLoaded),0);
	rb_define_method(rb_cCeguiScheme,"LookNFeels_loaded?",RUBY_METHOD_FUNC(_areLookNFeelsLoaded),0);
	rb_define_method(rb_cCeguiScheme,"WindowFactories_loaded?",RUBY_METHOD_FUNC(_areWindowFactoriesLoaded),0);
	rb_define_method(rb_cCeguiScheme,"WindowRendererFactories_loaded?",RUBY_METHOD_FUNC(_areWindowRendererFactoriesLoaded),0);
	rb_define_method(rb_cCeguiScheme,"FactoryAliases_loaded?",RUBY_METHOD_FUNC(_areFactoryAliasesLoaded),0);
	rb_define_method(rb_cCeguiScheme,"FalagardMappings_loaded?",RUBY_METHOD_FUNC(_areFalagardMappingsLoaded),0);



	rb_define_method(rb_cCeguiScheme,"each_XMLImagesets",RUBY_METHOD_FUNC(_each_XMLImagesets),0);
	rb_define_method(rb_cCeguiScheme,"each_ImageFileImagesets",RUBY_METHOD_FUNC(_each_ImageFileImagesets),0);
	rb_define_method(rb_cCeguiScheme,"each_Fonts",RUBY_METHOD_FUNC(_each_Fonts),0);
	rb_define_method(rb_cCeguiScheme,"each_LookNFeels",RUBY_METHOD_FUNC(_each_LookNFeels),0);

	rb_define_singleton_method(rb_cCeguiScheme,"[]",RUBY_METHOD_FUNC(_Manager_get),1);
	rb_define_singleton_method(rb_cCeguiScheme,"each",RUBY_METHOD_FUNC(_Manager_each),0);

	rb_define_singleton_method(rb_cCeguiScheme,"defined?",RUBY_METHOD_FUNC(_Manager_isDefined),1);

	rb_define_singleton_method(rb_cCeguiScheme,"new",RUBY_METHOD_FUNC(_Manager_create),-1);
	rb_define_singleton_method(rb_cCeguiScheme,"createAll",RUBY_METHOD_FUNC(_Manager_createAll),-1);

	rb_define_singleton_method(rb_cCeguiScheme,"defaultResourceGroup",RUBY_METHOD_FUNC(_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiScheme,"defaultResourceGroup=",RUBY_METHOD_FUNC(_Manager_setDefaultResourceGroup),1);

}
