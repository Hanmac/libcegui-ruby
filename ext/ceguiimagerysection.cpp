/*
 * ceguiimagerysection.cpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */

#include "ceguiimagerysection.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::ImagerySection*>(self)

VALUE rb_cCeguiImagerySection;
namespace CeguiImagerySection {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::ImagerySection);
}

macro_attr(Name,CEGUI::String)

macro_attr(MasterColours,CEGUI::ColourRect)

macro_attr(MasterColoursPropertySource,CEGUI::String)

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
	array[2]=rb_funcall(self,"name");
	return rb_f_sprintf(3,array);
}

/*
 *
 */
VALUE _getImageryComponentIterator(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getImageryComponentIterator());
	return self;
}
/*
 *
 */
VALUE _getTextComponentIterator(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getTextComponentIterator());
	return self;
}
/*
 *
 */
VALUE _getFrameComponentIterator(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getFrameComponentIterator());
	return self;
}


}

void Init_CeguiImagerySection(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiImagerySection,"name",1,1);
#endif
	using namespace CeguiImagerySection;

	rb_cCeguiImagerySection = rb_define_class_under(rb_mCegui,"ImagerySection",rb_cObject);

	rb_define_alloc_func(rb_cCeguiImagerySection,_alloc);

	rb_define_attr_method(rb_cCeguiImagerySection,"name",_getName,_setName);
	rb_define_method(rb_cCeguiImagerySection,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiImagerySection,"each_ImageryComponent",RUBY_METHOD_FUNC(_getImageryComponentIterator),0);
	rb_define_method(rb_cCeguiImagerySection,"each_TextComponent",RUBY_METHOD_FUNC(_getTextComponentIterator),0);
	rb_define_method(rb_cCeguiImagerySection,"each_FrameComponent",RUBY_METHOD_FUNC(_getFrameComponentIterator),0);
}


