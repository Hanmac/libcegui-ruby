/*
 * ceguiscrolledscrolleditemlistbase.hpp
 *
 *  Created on: 05.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiScrolledItemListBase_H__
#define __RubyCeguiScrolledItemListBase_H__

#include "main.hpp"
void Init_CeguiScrolledItemListBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiScrolledItemListBase;

//#include "ceguimenubase.hpp"

template <>
inline VALUE wrap< CEGUI::ScrolledItemListBase >(CEGUI::ScrolledItemListBase *scrolleditemlistbase )
{
	if(scrolleditemlistbase==NULL)
		return Qnil;
//	CEGUI::MenuBase *menubase = dynamic_cast<CEGUI::MenuBase*>(scrolleditemlistbase);
//	if(menubase)
//		return wrap(menubase);
	return RubyWindowHolder::get(scrolleditemlistbase,rb_cCeguiScrolledItemListBase);
}

template <>
inline CEGUI::ScrolledItemListBase* wrap< CEGUI::ScrolledItemListBase* >(const VALUE &vscrolleditemlistbase)
{
	return unwrapWindow<CEGUI::ScrolledItemListBase>(vscrolleditemlistbase, rb_cCeguiScrolledItemListBase);
}
#endif /* __RubyCeguiScrolledItemListBase_H__ */
