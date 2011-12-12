#include "ceguielement.hpp"

#define _self wrap<CEGUI::NamedElement*>(self)

VALUE rb_cCeguiNamedElement;

namespace CeguiNamedElement {

macro_attr(Name,CEGUI::String)


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
	array[2]=rb_funcall(self,rb_intern("name"),0);
	return rb_f_sprintf(3,array);
}


/*
*/
VALUE _isChild(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cCeguiElement)){
		return rb_call_super(1,&val);
	}
	return RBOOL(_self->isChild(wrap<CEGUI::String>(val)));
}
/*
*/
VALUE _isAncestor(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cCeguiElement)){
		return rb_call_super(1,&val);
	}
	return RBOOL(_self->isAncestor(wrap<CEGUI::String>(val)));
}


/*
*/
VALUE _removeChild(VALUE self,VALUE obj)
{
	if(rb_obj_is_kind_of(obj, rb_cCeguiElement)){
		return rb_call_super(1,&obj);
	}
	_self->removeChild(wrap<CEGUI::String>(obj));
	return self;
}
/*
*/
VALUE _getNamePath(VALUE self)
{
	return wrap(_self->getNamePath());
}

/*
 * call-seq:
 *   [] -> CEGUI::NamedElement
 * 
 * gets a child element
 * ===Return value
 * CEGUI::NamedElement or nil
*/
VALUE _get(VALUE self,VALUE name)
{
	if(_self->isChild(wrap<CEGUI::String>(name)))
		return wrap(_self->getChildElement(wrap<CEGUI::String>(name)));
	else
		return Qnil;
}

}
/*
*/
void Init_CeguiNamedElement(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiElement = rb_define_class_under(rb_mCegui,"Element",rb_cObject);
#endif
	using namespace CeguiNamedElement;

	rb_cCeguiNamedElement = rb_define_class_under(rb_mCegui,"NamedElement",rb_cCeguiElement);

	rb_define_attr_method(rb_cCeguiNamedElement,"name",_getName,_setName);
	
	rb_define_method(rb_cCeguiNamedElement,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	
	rb_define_method(rb_cCeguiNamedElement,"namePath",RUBY_METHOD_FUNC(_getNamePath),0);

	rb_define_method(rb_cCeguiNamedElement,"[]",RUBY_METHOD_FUNC(_get),1);

	rb_define_method(rb_cCeguiNamedElement,"isChild?",RUBY_METHOD_FUNC(_isChild),1);
	rb_define_method(rb_cCeguiNamedElement,"isAncestor?",RUBY_METHOD_FUNC(_isAncestor),1);
	
	rb_define_method(rb_cCeguiNamedElement,"removeChild",RUBY_METHOD_FUNC(_removeChild),1);
	
	
	rb_define_const(rb_cCeguiNamedElement,"EventNamespace",wrap(CEGUI::NamedElement::EventNamespace));
	rb_define_const(rb_cCeguiNamedElement,"EventNameChanged",wrap(CEGUI::NamedElement::EventNameChanged));
}
