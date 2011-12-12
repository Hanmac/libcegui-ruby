#include "ceguiitemlistbase.hpp"
#include "ceguiitementry.hpp"

#include "ceguiwindow.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::ItemListBase*>(self)
VALUE rb_cCeguiItemListBase;
/*
*/
VALUE CeguiItemListBase_each_item(VALUE self)
{
	try{
		for (unsigned int i = 0; i < _self->getItemCount(); ++i)
		{
			rb_yield(wrap(_self->getItemFromIndex(i)));
		}
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}


/*
*/
VALUE CeguiItemListBase_addItem(VALUE self,VALUE item)
{
	_self->addItem(wrap<CEGUI::ItemEntry*>(item));
	return self;
}
/*
*/
VALUE CeguiItemListBase_removeItem(VALUE self,VALUE item)
{
	_self->removeItem(wrap<CEGUI::ItemEntry*>(item));
	return self;
}

/*
*/
VALUE CeguiItemListBase_getItemRenderArea(VALUE self)
{
	return wrap(_self->getItemRenderArea());
}
/*
*/
VALUE CeguiItemListBase_getContentPane(VALUE self)
{
	return wrap(_self->getContentPane());
}
/*
*/
void Init_CeguiItemListBase(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_cCeguiWindow = rb_define_class_under(rb_mCegui,"Window",rb_cObject);

#endif

	rb_cCeguiItemListBase = rb_define_class_under(rb_mCegui,"ItemListBase",rb_cCeguiWindow);

	rb_define_method(rb_cCeguiItemListBase,"each_item",RUBY_METHOD_FUNC(CeguiItemListBase_each_item),0);

	rb_define_method(rb_cCeguiItemListBase,"addItem",RUBY_METHOD_FUNC(CeguiItemListBase_addItem),1);
	rb_define_method(rb_cCeguiItemListBase,"removeItem",RUBY_METHOD_FUNC(CeguiItemListBase_removeItem),1);

	rb_define_method(rb_cCeguiItemListBase,"itemRenderArea",RUBY_METHOD_FUNC(CeguiItemListBase_getItemRenderArea),0);
	rb_define_method(rb_cCeguiItemListBase,"contentPane",RUBY_METHOD_FUNC(CeguiItemListBase_getContentPane),0);

	rb_define_const(rb_cCeguiItemListBase,"EventNamespace",wrap(CEGUI::ItemListBase::EventNamespace));
	
	rb_define_const(rb_cCeguiItemListBase,"EventListContentsChanged",wrap(CEGUI::ItemListBase::EventListContentsChanged));
	rb_define_const(rb_cCeguiItemListBase,"EventSortEnabledChanged",wrap(CEGUI::ItemListBase::EventSortEnabledChanged));
	rb_define_const(rb_cCeguiItemListBase,"EventSortModeChanged",wrap(CEGUI::ItemListBase::EventSortModeChanged));
}
