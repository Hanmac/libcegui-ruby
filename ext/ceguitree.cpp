#include "ceguitree.hpp"

#include "ceguitreeitem.hpp"

#include "ceguiscrollbar.hpp"
#include "ceguiwindow.hpp"

#define _self wrap<CEGUI::Tree*>(self)
VALUE rb_cCeguiTree;

namespace CeguiTree {

singlefunc(resetList)
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
		result[0]=wrap(CEGUI::String(CEGUI::Tree::WidgetTypeName));
		result[1]=name;
		return rb_call_super(2,result);
	}
}
/*
*/
VALUE _addItem(VALUE self,VALUE item)
{
	_self->addItem(wrap<CEGUI::TreeItem*>(item));
	return self;
}
/*
*/
VALUE _insertItem(VALUE self,VALUE pos,VALUE item)
{
	_self->insertItem(wrap<CEGUI::TreeItem*>(pos),wrap<CEGUI::TreeItem*>(item));
	return self;
}
/*
*/
VALUE _removeItem(VALUE self,VALUE item)
{
	_self->removeItem(wrap<CEGUI::TreeItem*>(item));
	return self;
}

/*
*/
VALUE _each_selected(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	CEGUI::TreeItem *sel = _self->getFirstSelectedItem();
	while (sel)
	{
		rb_yield(wrap(sel));
		sel = _self->getNextSelected(sel);
	}
	return self;
}


/*
*/
VALUE _getVertScrollbar(VALUE self)
{
	return wrap(_self->getVertScrollbar());
}
/*
*/
VALUE _getHorzScrollbar(VALUE self)
{
	return wrap(_self->getHorzScrollbar());
}

}
/* Document-method: clear

*/

/*
*/
void Init_CeguiTree(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

#endif
	using namespace CeguiTree;
	rb_cCeguiTree = rb_define_class_under(rb_mCegui,"Tree",rb_cCeguiWindow);
	
	rb_define_singleton_method(rb_cCeguiTree,"new",RUBY_METHOD_FUNC(_new),-1);



	rb_define_method(rb_cCeguiTree,"addItem",RUBY_METHOD_FUNC(_addItem),1);
	rb_define_method(rb_cCeguiTree,"insertItem",RUBY_METHOD_FUNC(_insertItem),2);
	rb_define_method(rb_cCeguiTree,"removeItem",RUBY_METHOD_FUNC(_removeItem),1);
	
	rb_define_method(rb_cCeguiTree,"each_selected",RUBY_METHOD_FUNC(_each_selected),0);
	
	rb_define_method(rb_cCeguiTree,"vertScrollbar",RUBY_METHOD_FUNC(_getVertScrollbar),0);
	rb_define_method(rb_cCeguiTree,"horzScrollbar",RUBY_METHOD_FUNC(_getHorzScrollbar),0);
	
	rb_define_method(rb_cCeguiTree,"clear",RUBY_METHOD_FUNC(_resetList),0);
	
	rb_define_const(rb_cCeguiTree,"EventNamespace",wrap(CEGUI::Tree::EventNamespace));
	rb_define_const(rb_cCeguiTree,"WidgetTypeName",wrap(CEGUI::Tree::WidgetTypeName));	
	
	rb_define_const(rb_cCeguiTree,"EventListContentsChanged",wrap(CEGUI::Tree::EventListContentsChanged));
	rb_define_const(rb_cCeguiTree,"EventSelectionChanged",wrap(CEGUI::Tree::EventSelectionChanged));
	rb_define_const(rb_cCeguiTree,"EventSortModeChanged",wrap(CEGUI::Tree::EventSortModeChanged));
	rb_define_const(rb_cCeguiTree,"EventMultiselectModeChanged",wrap(CEGUI::Tree::EventMultiselectModeChanged));
	rb_define_const(rb_cCeguiTree,"EventVertScrollbarModeChanged",wrap(CEGUI::Tree::EventVertScrollbarModeChanged));
	rb_define_const(rb_cCeguiTree,"EventHorzScrollbarModeChanged",wrap(CEGUI::Tree::EventHorzScrollbarModeChanged));

}
