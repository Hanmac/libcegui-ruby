/*
 * ceguilistheadersegment.hpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */

#ifndef __RubyCeguiListHeaderSegment_H__
#define __RubyCeguiListHeaderSegment_H__

#include "main.hpp"
void Init_CeguiListHeaderSegment(VALUE rb_mCegui);
extern VALUE rb_cCeguiListHeaderSegment;

#include "ceguiwindowimpl.hpp"


template <>
inline VALUE wrap< CEGUI::ListHeaderSegment >(CEGUI::ListHeaderSegment *listheader )
{
	return RubyWindowHolder::get(listheader,rb_cCeguiListHeaderSegment);
}

template <>
inline VALUE wrap< CEGUI::ListHeaderSegment >(const CEGUI::ListHeaderSegment &listheader )
{
	return wrap< CEGUI::ListHeaderSegment >(const_cast<CEGUI::ListHeaderSegment*>(&listheader));
}


template <>
inline CEGUI::ListHeaderSegment* wrap< CEGUI::ListHeaderSegment* >(const VALUE &vlistheader)
{
	return unwrapWindow<CEGUI::ListHeaderSegment>(vlistheader, rb_cCeguiListHeaderSegment);
}

template <>
inline const CEGUI::ListHeaderSegment& wrap< const CEGUI::ListHeaderSegment& >(const VALUE &vlistheader)
{
	return *wrap< CEGUI::ListHeaderSegment* >(vlistheader);
}
#endif /* __RubyCeguiListHeaderSegment_H__ */
