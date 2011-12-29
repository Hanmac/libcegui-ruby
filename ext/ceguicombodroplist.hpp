#ifndef __RubyCeguiComboDropList_H__
#define __RubyCeguiComboDropList_H__

#include "main.hpp"
void Init_CeguiComboDropList(VALUE rb_mCegui);
extern VALUE rb_cCeguiComboDropList;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::ComboDropList >(CEGUI::ComboDropList *list )
{
	return RubyWindowHolder::get(list,rb_cCeguiComboDropList);
}

template <>
inline CEGUI::ComboDropList* wrap< CEGUI::ComboDropList* >(const VALUE &vlist)
{
	return unwrapWindow<CEGUI::ComboDropList>(vlist, rb_cCeguiComboDropList);
}
#endif /* __RubyCeguiComboDropList_H__ */
