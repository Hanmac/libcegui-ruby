/*
 * ceguisectionspecification.cpp
 *
 *  Created on: 22.12.2011
 *      Author: hanmac
 */


#include "ceguisectionspecification.hpp"

#include "ceguiexception.hpp"


#define _self wrap<CEGUI::SectionSpecification*>(self)

VALUE rb_cCeguiSectionSpecification;
namespace CeguiSectionSpecification {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::SectionSpecification);
}
macro_attr(OwnerWidgetLookFeel,CEGUI::String)
macro_attr(SectionName,CEGUI::String)

//TODO make it better with internal check
macro_attr(OverrideColours,CEGUI::ColourRect)
macro_attr(OverrideColoursPropertySource,CEGUI::String)
macro_attr_bool(UsingOverrideColours)


macro_attr(RenderControlPropertySource,CEGUI::String)
macro_attr(RenderControlValue,CEGUI::String)
macro_attr(RenderControlWidget,CEGUI::String)

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

}

void Init_CeguiSectionSpecification(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiSectionSpecification,"ownerWidgetLookFeel",1,1);

	rb_define_attr(rb_cCeguiSectionSpecification,"name",1,1);

	rb_define_attr(rb_cCeguiSectionSpecification,"overrideColours",1,1);
	rb_define_attr(rb_cCeguiSectionSpecification,"overrideColoursPropertySource",1,1);
	rb_define_attr(rb_cCeguiSectionSpecification,"usingOverrideColours",1,1);


	rb_define_attr(rb_cCeguiSectionSpecification,"renderControlPropertySource",1,1);
	rb_define_attr(rb_cCeguiSectionSpecification,"renderControlValue",1,1);
	rb_define_attr(rb_cCeguiSectionSpecification,"renderControlWidget",1,1);
#endif
	using namespace CeguiSectionSpecification;

	rb_cCeguiSectionSpecification = rb_define_class_under(rb_mCegui,"SectionSpecification",rb_cObject);

	rb_define_alloc_func(rb_cCeguiSectionSpecification,_alloc);

	rb_define_attr_method(rb_cCeguiSectionSpecification,"ownerWidgetLookFeel",_getOwnerWidgetLookFeel,_setOwnerWidgetLookFeel);

	rb_define_attr_method(rb_cCeguiSectionSpecification,"name",_getSectionName,_setSectionName);

	rb_define_attr_method(rb_cCeguiSectionSpecification,"overrideColours",_getOverrideColours,_setOverrideColours);
	rb_define_attr_method(rb_cCeguiSectionSpecification,"usingOverrideColours",_getUsingOverrideColours,_setUsingOverrideColours);
	rb_define_attr_method(rb_cCeguiSectionSpecification,"overrideColoursPropertySource",_getOverrideColoursPropertySource,_setOverrideColoursPropertySource);

	rb_define_attr_method(rb_cCeguiSectionSpecification,"renderControlPropertySource",_getRenderControlPropertySource,_setRenderControlPropertySource);
	rb_define_attr_method(rb_cCeguiSectionSpecification,"renderControlValue",_getRenderControlValue,_setRenderControlValue);
	rb_define_attr_method(rb_cCeguiSectionSpecification,"renderControlWidget",_getRenderControlWidget,_setRenderControlWidget);


	rb_define_method(rb_cCeguiSectionSpecification,"inspect",RUBY_METHOD_FUNC(_inspect),0);


}



