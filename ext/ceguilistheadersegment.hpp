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
inline CEGUI::ListHeaderSegment* wrap< CEGUI::ListHeaderSegment* >(const VALUE &vlistheader)
{
	if (rb_obj_is_kind_of(vlistheader, rb_cCeguiListHeaderSegment)){
		return (CEGUI::ListHeaderSegment*)(wrap< CEGUI::Window* >(vlistheader));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiListHeaderSegment),rb_obj_classname(vlistheader));
		return NULL;
	}
}
#endif /* __RubyCeguiListHeaderSegment_H__ */
