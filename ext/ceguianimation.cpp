#include "ceguianimation.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Animation*>(self)
#define _manager CEGUI::AnimationManager::getSingletonPtr()

VALUE rb_cCeguiAnimation;
namespace CeguiAnimation {

macro_attr(Duration,float)
macro_attr(AutoStart,bool)
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

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _self->getNumAffectors(); ++i)
		rb_yield(wrap( _self->getAffectorAtIdx(i)));
	return self;
}


/*
*/
VALUE _get(VALUE self,VALUE id)
{
	if(NUM2UINT(id) < _self->getNumAffectors())
		return wrap((_self)->getAffectorAtIdx(NUM2UINT(id)));
	return Qnil;
}

/*
*/
VALUE _Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::AnimationManager::getDefaultResourceGroup());
}
/*
*/
VALUE _Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::AnimationManager::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}

/*
*/
VALUE _Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (unsigned int i = 0; i < _manager->getNumAnimations(); ++i)
		rb_yield(wrap(_manager->getAnimationAtIdx(i)));
	return self;
}

/*
*/
VALUE _Manager_get(VALUE self,VALUE name)
{
	if (rb_obj_is_kind_of(name, rb_cInteger)){
		if(_manager->getNumAnimations() > NUM2UINT(name))
			return wrap(_manager->getAnimationAtIdx(NUM2INT(name)));
	}else{
		if(_manager->isAnimationPresent(wrap<CEGUI::String>(name)))
			return wrap(_manager->getAnimation(wrap<CEGUI::String>(name)));
	}
	return Qnil;
}

}
/*
 *
 */
void Init_CeguiAnimation(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	
	rb_define_attr(rb_cCeguiAnimation,"duration",1,1);
	rb_define_attr(rb_cCeguiAnimation,"autostart",1,1);
#endif
	using namespace CeguiAnimation;

	rb_cCeguiAnimation = rb_define_class_under(rb_mCegui,"Animation",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiAnimation);

	rb_define_method(rb_cCeguiAnimation,"[]",RUBY_METHOD_FUNC(_get),1);
	rb_define_method(rb_cCeguiAnimation,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cCeguiAnimation,rb_mEnumerable);

	rb_extend_object(rb_cCeguiAnimation,rb_mEnumerable);

	rb_define_attr_method(rb_cCeguiAnimation,"duration",
		_getDuration,_setDuration);
	rb_define_attr_method(rb_cCeguiAnimation,"autostart",
		_getAutoStart,_setAutoStart);

	rb_define_method(rb_cCeguiAnimation,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cCeguiAnimation,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_singleton_method(rb_cCeguiAnimation,"[]",RUBY_METHOD_FUNC(_Manager_get),1);
	rb_define_singleton_method(rb_cCeguiAnimation,"each",RUBY_METHOD_FUNC(_Manager_each),0);

	rb_define_singleton_method(rb_cCeguiAnimation,"defaultResourceGroup",RUBY_METHOD_FUNC(_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiAnimation,"defaultResourceGroup=",RUBY_METHOD_FUNC(_Manager_setDefaultResourceGroup),1);

}
