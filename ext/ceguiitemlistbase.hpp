#ifndef __RubyCeguiItemListBase_H__
#define __RubyCeguiItemListBase_H__

#include "main.hpp"
void Init_CeguiItemListBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiItemListBase;

#include "ceguimenubase.hpp"
#include "ceguiscrolleditemlistbase.hpp"

template <>
inline VALUE wrap< CEGUI::ItemListBase >(CEGUI::ItemListBase *itemlistbase )
{
	if(itemlistbase==NULL)
		return Qnil;
	CEGUI::MenuBase *menubase = dynamic_cast<CEGUI::MenuBase*>(itemlistbase);
	if(menubase)
		return wrap(menubase);
	CEGUI::ScrolledItemListBase *scrolleditemlistbase = dynamic_cast<CEGUI::ScrolledItemListBase*>(itemlistbase);
	if(scrolleditemlistbase)
		return wrap(scrolleditemlistbase);

	return RubyWindowHolder::get(itemlistbase,rb_cCeguiItemListBase);
}

template <>
inline CEGUI::ItemListBase* wrap< CEGUI::ItemListBase* >(const VALUE &vitemlistbase)
{
	return unwrapWindow<CEGUI::ItemListBase>(vitemlistbase, rb_cCeguiItemListBase);
}
#endif /* __RubyCeguiItemListBase_H__ */
