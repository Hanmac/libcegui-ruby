/*
 * ceguiscrolleditemlistbase.cpp
 *
 *  Created on: 05.12.2011
 *      Author: hanmac
 */

#include "ceguiwindow.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::ScrolledItemListBase*>(self)
VALUE rb_cCeguiScrolledItemListBase;
namespace CeguiScrolledItemListBase {

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
/*
*/
void Init_CeguiScrolledItemListBase(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);
	rb_cCeguiItemListBase = rb_define_class_under(rb_mCegui,"ItemListBase",rb_cCeguiWindow);

	rb_define_attr(rb_cCeguiScrolledItemListBase,"showVertScrollbar",1,1);
	rb_define_attr(rb_cCeguiScrolledItemListBase,"showHorzScrollbar",1,1);

#endif
	using namespace CeguiScrolledItemListBase;

	rb_cCeguiScrolledItemListBase = rb_define_class_under(rb_mCegui,"ScrolledItemListBase",rb_cCeguiItemListBase);

	rb_define_const(rb_cCeguiScrolledItemListBase,"EventNamespace",wrap(CEGUI::ScrolledItemListBase::EventNamespace));

	rb_define_attr_method(rb_cCeguiScrolledItemListBase,"showVertScrollbar",_getShowVertScrollbar,_setShowVertScrollbar);
	rb_define_attr_method(rb_cCeguiScrolledItemListBase,"showHorzScrollbar",_getShowHorzScrollbar,_setShowHorzScrollbar);

	rb_define_method(rb_cCeguiScrolledItemListBase,"vertScrollbar",RUBY_METHOD_FUNC(_getVertScrollbar),0);
	rb_define_method(rb_cCeguiScrolledItemListBase,"horzScrollbar",RUBY_METHOD_FUNC(_getHorzScrollbar),0);


	rb_define_const(rb_cCeguiItemListBase,"VertScrollbarName",wrap(CEGUI::ScrolledItemListBase::VertScrollbarName));
	rb_define_const(rb_cCeguiItemListBase,"HorzScrollbarName",wrap(CEGUI::ScrolledItemListBase::HorzScrollbarName));
	rb_define_const(rb_cCeguiItemListBase,"ContentPaneName",wrap(CEGUI::ScrolledItemListBase::ContentPaneName));
	rb_define_const(rb_cCeguiItemListBase,"EventVertScrollbarModeChanged",wrap(CEGUI::ScrolledItemListBase::EventVertScrollbarModeChanged));
	rb_define_const(rb_cCeguiItemListBase,"EventHorzScrollbarModeChanged",wrap(CEGUI::ScrolledItemListBase::EventHorzScrollbarModeChanged));
}
