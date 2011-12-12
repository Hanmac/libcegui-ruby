/*
 * ceguilistheader.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
/*
 * ceguitabcontrol.cpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::ListHeader*>(self)
VALUE rb_cCeguiListHeader;

namespace CeguiListHeader {

macro_attr_bool(SortingEnabled)
macro_attr_bool(ColumnSizingEnabled)
macro_attr_bool(ColumnDraggingEnabled)

macro_attr(SortSegment,CEGUI::ListHeaderSegment)
macro_attr(SortColumn,uint)

/*
*/
VALUE _new(int argc,VALUE *argv,VALUE self)
{
	VALUE name;
	rb_scan_args(argc, argv, "01",&name);
	VALUE result[2];
	result[0]=wrap(CEGUI::String(CEGUI::ListHeader::WidgetTypeName));
	result[1]=name;
	return rb_call_super(2,result);
}

}
/*
*/
void Init_CeguiListHeader(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiListHeader,"sortingEnabled",1,1);
	rb_define_attr(rb_cCeguiListHeader,"columnSizingEnabled",1,1);
	rb_define_attr(rb_cCeguiListHeader,"columnDraggingEnabled",1,1);

	rb_define_attr(rb_cCeguiListHeader,"sortSegment",1,1);
	rb_define_attr(rb_cCeguiListHeader,"sortColumn",1,1);
#endif
	using namespace CeguiListHeader;

	rb_cCeguiListHeader = rb_define_class_under(rb_mCegui,"ListHeader",rb_cCeguiWindow);

	rb_define_attr_method(rb_cCeguiListHeader,"sortingEnabled",_getSortingEnabled,_setSortingEnabled);
	rb_define_attr_method(rb_cCeguiListHeader,"columnSizingEnabled",_getColumnSizingEnabled,_setColumnSizingEnabled);
	rb_define_attr_method(rb_cCeguiListHeader,"columnDraggingEnabled",_getColumnDraggingEnabled,_setColumnDraggingEnabled);

	rb_define_attr_method(rb_cCeguiListHeader,"sortSegment",_getSortSegment,_setSortSegment);
	rb_define_attr_method(rb_cCeguiListHeader,"sortColumn",_getSortColumn,_setSortColumn);

	rb_define_singleton_method(rb_cCeguiListHeader,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_const(rb_cCeguiListHeader,"WidgetTypeName",wrap(CEGUI::ListHeader::WidgetTypeName));
	rb_define_const(rb_cCeguiListHeader,"EventNamespace",wrap(CEGUI::ListHeader::EventNamespace));

}



