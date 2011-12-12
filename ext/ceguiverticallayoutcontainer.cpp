/*
 * ceguiverticallayoutcontainer.cpp
 *
 *  Created on: 11.12.2011
 *      Author: hanmac
 */

#include "ceguiwindow.hpp"

//#define _self wrap<CEGUI::SequentialLayoutContainer*>(self)
VALUE rb_cCeguiVerticalLayoutContainer;

namespace CeguiVerticalLayoutContainer {

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::VerticalLayoutContainer::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}


}

/*
*/
void Init_CeguiVerticalLayoutContainer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiLayoutContainer = rb_define_class_under(rb_mCegui,"LayoutContainer",rb_cCeguiWindow);
	rb_cCeguiSequentialLayoutContainer = rb_define_class_under(rb_mCegui,"SequentialLayoutContainer",rb_cCeguiLayoutContainer);
#endif
	using namespace CeguiVerticalLayoutContainer;

	rb_cCeguiVerticalLayoutContainer = rb_define_class_under(rb_mCegui,"VerticalLayoutContainer",rb_cCeguiSequentialLayoutContainer);

	rb_define_singleton_method(rb_cCeguiVerticalLayoutContainer,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiVerticalLayoutContainer,"WidgetTypeName",wrap(CEGUI::VerticalLayoutContainer::WidgetTypeName));

}
