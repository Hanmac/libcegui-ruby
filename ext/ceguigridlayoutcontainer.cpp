/*
 * ceguigridlayoutcontainer.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */

#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::GridLayoutContainer*>(self)
VALUE rb_cCeguiGridLayoutContainer;

namespace CeguiGridLayoutContainer {

macro_attr(Grid,CEGUI::Sizef)

/*
 */
VALUE _swapChildren(VALUE self,VALUE obj1,VALUE obj2)
{
	CEGUI::Window *cobj1, *cobj2;
	if(rb_obj_is_kind_of(obj1, rb_cCeguiWindow)) {
		cobj1 = wrap<CEGUI::Window*>(obj1);
	}else if(rb_obj_is_kind_of(obj1, rb_cString)) {
		cobj1 = _self->getChild(wrap<CEGUI::String>(obj1));
	}
	if(rb_obj_is_kind_of(obj2, rb_cCeguiWindow)) {
		cobj2 = wrap<CEGUI::Window*>(obj2);
	}else if(rb_obj_is_kind_of(obj1, rb_cString)) {
		cobj2 = _self->getChild(wrap<CEGUI::String>(obj2));
	}
	_self->swapChildren(cobj1,cobj2);
	return self;
}

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::GridLayoutContainer::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}



}

/*
*/
void Init_CeguiGridLayoutContainer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiLayoutContainer = rb_define_class_under(rb_mCegui,"LayoutContainer",rb_cCeguiWindow);

	rb_define_attr(rb_cCeguiGridLayoutContainer,"grid",1,1);
#endif
	using namespace CeguiGridLayoutContainer;

	rb_cCeguiGridLayoutContainer = rb_define_class_under(rb_mCegui,"GridLayoutContainer",rb_cCeguiLayoutContainer);

	rb_define_attr_method(rb_cCeguiGridLayoutContainer,"grid",_getGrid,_setGrid);

	rb_define_method(rb_cCeguiGridLayoutContainer,"swap",RUBY_METHOD_FUNC(_swapChildren),-1);

	rb_define_singleton_method(rb_cCeguiGridLayoutContainer,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiGridLayoutContainer,"WidgetTypeName",wrap(CEGUI::GridLayoutContainer::WidgetTypeName));

}
