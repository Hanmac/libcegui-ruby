/*
 * ceguiclippedcontainer.cpp
 *
 *  Created on: 02.12.2011
 *      Author: hanmac
 */
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::ClippedContainer*>(self)
VALUE rb_cCeguiClippedContainer;

namespace CeguiClippedContainer {

macro_attr(ClipArea,CEGUI::Rectf)
macro_attr(ClipperWindow,CEGUI::Window*)

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	if(argc==2)
		return rb_call_super(2,argv);
	else{
		rb_scan_args(argc, argv, "01",&name);
		VALUE result[2];
		result[0]=wrap(CEGUI::String(CEGUI::ClippedContainer::WidgetTypeName));
		result[1]=name;
		return rb_call_super(2,result);
	}
}

}

/*
*/
void Init_CeguiClippedContainer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiClippedContainer,"clipArea",1,1);
	rb_define_attr(rb_cCeguiClippedContainer,"clipperWindow",1,1);
#endif
	using namespace CeguiClippedContainer;

	rb_cCeguiClippedContainer = rb_define_class_under(rb_mCegui,"ClippedContainer",rb_cCeguiWindow);

	rb_define_attr_method(rb_cCeguiClippedContainer,"clipArea",_getClipArea,_setClipArea);
	rb_define_attr_method(rb_cCeguiClippedContainer,"clipperWindow",_getClipperWindow,_setClipperWindow);


	rb_define_singleton_method(rb_cCeguiClippedContainer,"new",RUBY_METHOD_FUNC(_new),-1);


	rb_define_const(rb_cCeguiClippedContainer,"EventNamespace",wrap(CEGUI::ClippedContainer::EventNamespace));
	rb_define_const(rb_cCeguiClippedContainer,"WidgetTypeName",wrap(CEGUI::ClippedContainer::WidgetTypeName));

}
