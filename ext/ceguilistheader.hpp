/*
 * ceguilistheader.hpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiListHeader_H__
#define __RubyCeguiListHeader_H__

#include "main.hpp"
void Init_CeguiListHeader(VALUE rb_mCegui);
extern VALUE rb_cCeguiListHeader;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::ListHeader >(CEGUI::ListHeader *listheader )
{
	return RubyWindowHolder::get(listheader,rb_cCeguiListHeader);
}

template <>
inline CEGUI::ListHeader* wrap< CEGUI::ListHeader* >(const VALUE &vlistheader)
{
	return unwrapWindow<CEGUI::ListHeader>(vlistheader, rb_cCeguiListHeader);
}
#endif /* __RubyCeguiListHeader_H__ */
