#include "ceguilistboxitem.hpp"

#include "ceguiscrollbar.hpp"
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::MultiColumnList*>(self)
VALUE rb_cCeguiMultiColumnList;

namespace CeguiMultiColumnList {

singlefunc(resetList)



singlereturn(getHorzScrollbar)
singlereturn(getVertScrollbar)
singlereturn(getListHeader)

singlereturn(getColumnCount)
singlereturn(getRowCount)

macro_attr(NominatedSelectionColumnID,uint)
macro_attr(NominatedSelectionColumn,uint)
macro_attr(NominatedSelectionRow,uint)

macro_attr(SortColumn,uint)

macro_attr(SelectionMode,CEGUI::MultiColumnList::SelectionMode)
macro_attr(SortDirection,CEGUI::ListHeaderSegment::SortDirection)

macro_attr_bool(UserSortControlEnabled)
macro_attr_bool(UserColumnSizingEnabled)
macro_attr_bool(UserColumnDraggingEnabled)

VALUE _getShowVertScrollbar(VALUE self)
{
	return wrap(_self->isVertScrollbarAlwaysShown());
}
VALUE _setShowVertScrollbar(VALUE self,VALUE val)
{
	_self->setShowVertScrollbar(wrap<bool>(val));
	return val;
}

VALUE _getShowHorzScrollbar(VALUE self)
{
	return wrap(_self->isHorzScrollbarAlwaysShown());
}
VALUE _setShowHorzScrollbar(VALUE self,VALUE val)
{
	_self->setShowHorzScrollbar(wrap<bool>(val));
	return val;
}

/*
 *
 */
VALUE _getItemColumnIndex(VALUE self,VALUE item)
{
	if(_self->isListboxItemInList(wrap<CEGUI::ListboxItem*>(item)))
		return UINT2NUM(_self->getItemColumnIndex(wrap<CEGUI::ListboxItem*>(item)));
	return Qnil;
}
/*
 *
 */
VALUE _getItemRowIndex(VALUE self,VALUE item)
{
	if(_self->isListboxItemInList(wrap<CEGUI::ListboxItem*>(item)))
		return UINT2NUM(_self->getItemRowIndex(wrap<CEGUI::ListboxItem*>(item)));
	return Qnil;
}

/*
 *
 */
VALUE _index(VALUE self,VALUE item)
{
	if (rb_obj_is_kind_of(item, rb_cCeguiListboxItem)){
		if(_self->isListboxItemInList(wrap<CEGUI::ListboxItem*>(item)))
			return wrap(_self->getItemGridReference(wrap<CEGUI::ListboxItem*>(item)));
		return Qnil;
	}else
		return rb_call_super(1,&item);
}

/*
 *
 */
VALUE _include(VALUE self,VALUE item)
{
	if (rb_obj_is_kind_of(item, rb_cCeguiListboxItem)){
		return wrap(_self->isListboxItemInList(wrap<CEGUI::ListboxItem*>(item)));
	}else
		return rb_call_super(1,&item);
}
/*
 *
 */
VALUE _includeColumn(VALUE self,VALUE item,VALUE col)
{
	if(NUM2UINT(col) < _self->getColumnCount())
		return wrap(_self->isListboxItemInColumn(wrap<CEGUI::ListboxItem*>(item),NUM2UINT(col)));
	return Qfalse;
}
/*
 *
 */
VALUE _includeRow(VALUE self,VALUE item,VALUE row)
{
	if(NUM2UINT(row) < _self->getRowCount())
		return wrap(_self->isListboxItemInRow(wrap<CEGUI::ListboxItem*>(item),NUM2UINT(row)));
	return Qfalse;
}

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
		result[0]=wrap(CEGUI::String(CEGUI::MultiColumnList::WidgetTypeName));
		result[1]=name;
		return rb_call_super(2,result);
	}
}

/*
*/
VALUE _get(int argc,VALUE *argv,VALUE self)
{
	VALUE x,y;
	rb_scan_args(argc, argv, "11",&x,&y);
	if(argc==2)
	{
		return wrap(_self->getItemAtGridReference(CEGUI::MCLGridRef(NUM2INT(x),NUM2INT(y))));
	}
	return rb_call_super(argc,argv);
}

/*
*/
VALUE _each_item(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);

	for(uint r = 0; r < _self->getRowCount(); ++r)
		for(uint c = 0; c < _self->getColumnCount(); ++c)
			rb_yield_values(3,UINT2NUM(r),UINT2NUM(c),wrap(_self->getItemAtGridReference(CEGUI::MCLGridRef(r,c))));
	return self;
}

/*
*/
VALUE _each_selected(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	CEGUI::ListboxItem *sel = _self->getFirstSelectedItem();
	while (sel)
	{
		rb_yield(wrap(sel));
		sel = _self->getNextSelected(sel);
	}
	return self;
}

/*
 */
VALUE _each_column(VALUE self,VALUE col)
{
	RETURN_ENUMERATOR(self,1,&col);

	if(_self->getColumnCount() < NUM2UINT(col))
	{
		for(uint i = 0; i < _self->getRowCount(); ++i)
		{
			rb_yield(wrap(_self->getItemAtGridReference(CEGUI::MCLGridRef(i,NUM2INT(col)))));
		}
	}
	return self;
}

/*
 */
VALUE _each_row(VALUE self,VALUE row)
{
	RETURN_ENUMERATOR(self,1,&row);

	if(_self->getRowCount() < NUM2UINT(row))
	{
		for(uint i = 0; i < _self->getColumnCount(); ++i)
		{
			rb_yield(wrap(_self->getItemAtGridReference(CEGUI::MCLGridRef(NUM2INT(row),i))));
		}
	}
	return self;
}

}
/* Document-method: clear
*/
/* Document-method: vertScrollbar
*/
/* Document-method: horzScrollbar
*/
/* Document-method: listHeader
*/

/*
*/
void Init_CeguiMultiColumnList(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

	rb_define_attr(rb_cCeguiMultiColumnList,"showVertScrollbar",1,1);
	rb_define_attr(rb_cCeguiMultiColumnList,"showHorzScrollbar",1,1);

	rb_define_attr(rb_cCeguiMultiColumnList,"userSortControlEnabled",1,1);
	rb_define_attr(rb_cCeguiMultiColumnList,"userColumnSizingEnabled",1,1);
	rb_define_attr(rb_cCeguiMultiColumnList,"userColumnDraggingEnabled",1,1);u
#endif
	using namespace CeguiMultiColumnList;

	rb_cCeguiMultiColumnList = rb_define_class_under(rb_mCegui,"MultiColumnList",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiMultiColumnList,"new",RUBY_METHOD_FUNC(_new),-1);

	rb_define_attr_method(rb_cCeguiMultiColumnList,"showVertScrollbar",_getShowVertScrollbar,_setShowVertScrollbar);
	rb_define_attr_method(rb_cCeguiMultiColumnList,"showHorzScrollbar",_getShowHorzScrollbar,_setShowHorzScrollbar);

	rb_define_attr_method(rb_cCeguiMultiColumnList,"userSortControlEnabled",_getUserSortControlEnabled,_setUserSortControlEnabled);
	rb_define_attr_method(rb_cCeguiMultiColumnList,"userColumnSizingEnabled",_getUserColumnSizingEnabled,_setUserColumnSizingEnabled);
	rb_define_attr_method(rb_cCeguiMultiColumnList,"userColumnDraggingEnabled",_getUserColumnDraggingEnabled,_setUserColumnDraggingEnabled);

	rb_define_method(rb_cCeguiMultiColumnList,"each_item",RUBY_METHOD_FUNC(_each_item),0);
	rb_define_method(rb_cCeguiMultiColumnList,"each_selected",RUBY_METHOD_FUNC(_each_selected),0);

	rb_define_method(rb_cCeguiMultiColumnList,"each_column",RUBY_METHOD_FUNC(_each_column),1);
	rb_define_method(rb_cCeguiMultiColumnList,"each_row",RUBY_METHOD_FUNC(_each_row),1);

	rb_define_method(rb_cCeguiMultiColumnList,"column_index",RUBY_METHOD_FUNC(_getItemColumnIndex),1);
	rb_define_method(rb_cCeguiMultiColumnList,"row_index",RUBY_METHOD_FUNC(_getItemRowIndex),1);
	
	rb_define_method(rb_cCeguiMultiColumnList,"[]",RUBY_METHOD_FUNC(_get),-1);
	rb_define_method(rb_cCeguiMultiColumnList,"index",RUBY_METHOD_FUNC(_index),1);
	rb_define_method(rb_cCeguiMultiColumnList,"include?",RUBY_METHOD_FUNC(_include),1);
	rb_define_method(rb_cCeguiMultiColumnList,"includeColumn?",RUBY_METHOD_FUNC(_includeColumn),2);
	rb_define_method(rb_cCeguiMultiColumnList,"includeRow?",RUBY_METHOD_FUNC(_includeRow),2);

	rb_define_method(rb_cCeguiMultiColumnList,"vertScrollbar",RUBY_METHOD_FUNC(_getVertScrollbar),0);
	rb_define_method(rb_cCeguiMultiColumnList,"horzScrollbar",RUBY_METHOD_FUNC(_getHorzScrollbar),0);
	rb_define_method(rb_cCeguiMultiColumnList,"listHeader",RUBY_METHOD_FUNC(_getListHeader),0);
	

	rb_define_method(rb_cCeguiMultiColumnList,"clear",RUBY_METHOD_FUNC(_resetList),0);
	
	rb_define_const(rb_cCeguiMultiColumnList,"EventNamespace",wrap(CEGUI::MultiColumnList::EventNamespace));
	rb_define_const(rb_cCeguiMultiColumnList,"WidgetTypeName",wrap(CEGUI::MultiColumnList::WidgetTypeName));

	rb_define_const(rb_cCeguiMultiColumnList,"EventSelectionModeChanged",wrap(CEGUI::MultiColumnList::EventSelectionModeChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventNominatedSelectColumnChanged",wrap(CEGUI::MultiColumnList::EventNominatedSelectColumnChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventNominatedSelectRowChanged",wrap(CEGUI::MultiColumnList::EventNominatedSelectRowChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventVertScrollbarModeChanged",wrap(CEGUI::MultiColumnList::EventVertScrollbarModeChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventHorzScrollbarModeChanged",wrap(CEGUI::MultiColumnList::EventHorzScrollbarModeChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventSelectionChanged",wrap(CEGUI::MultiColumnList::EventSelectionChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventListContentsChanged",wrap(CEGUI::MultiColumnList::EventListContentsChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventSortColumnChanged",wrap(CEGUI::MultiColumnList::EventSortColumnChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventSortDirectionChanged",wrap(CEGUI::MultiColumnList::EventSortDirectionChanged));
	rb_define_const(rb_cCeguiMultiColumnList,"EventListColumnSized",wrap(CEGUI::MultiColumnList::EventListColumnSized));
	rb_define_const(rb_cCeguiMultiColumnList,"EventListColumnMoved",wrap(CEGUI::MultiColumnList::EventListColumnMoved));

	rb_define_const(rb_cCeguiMultiColumnList,"VertScrollbarName",wrap(CEGUI::MultiColumnList::VertScrollbarName));
	rb_define_const(rb_cCeguiMultiColumnList,"HorzScrollbarName",wrap(CEGUI::MultiColumnList::HorzScrollbarName));
	rb_define_const(rb_cCeguiMultiColumnList,"ListHeaderName",wrap(CEGUI::MultiColumnList::ListHeaderName));

}
