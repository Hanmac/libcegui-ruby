/*
 * ceguimulticolumnlist.hpp
 *
 *  Created on: 26.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiMultiColumnList_H__
#define __RubyCeguiMultiColumnList_H__

#include "main.hpp"
void Init_CeguiMultiColumnList(VALUE rb_mCegui);
extern VALUE rb_cCeguiMultiColumnList;

#include "ceguicombodroplist.hpp"

template <>
inline VALUE wrap< CEGUI::MCLGridRef >(const CEGUI::MCLGridRef &ref )
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,UINT2NUM(ref.row));
	rb_ary_push(result,UINT2NUM(ref.column));
	return result;
}



template <>
inline VALUE wrap< CEGUI::MultiColumnList >(CEGUI::MultiColumnList *list )
{
	return RubyWindowHolder::get(list,rb_cCeguiMultiColumnList);
}

template <>
inline CEGUI::MultiColumnList* wrap< CEGUI::MultiColumnList* >(const VALUE &vlist)
{
	return unwrapWindow<CEGUI::MultiColumnList>(vlist, rb_cCeguiMultiColumnList);
}
#endif /* __RubyCeguiMultiColumnList_H__ */
