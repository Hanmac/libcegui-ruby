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
	if (rb_obj_is_kind_of(vlistheader, rb_cCeguiListHeader)){
		return (CEGUI::ListHeader*)(wrap< CEGUI::Window* >(vlistheader));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiListHeader),rb_obj_classname(vlistheader));
		return NULL;
	}
}
#endif /* __RubyCeguiListHeader_H__ */
