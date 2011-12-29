/*
 * ceguimousecursor.hpp
 *
 *  Created on: 21.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiMouseCursor_H__
#define __RubyCeguiMouseCursor_H__

#include "ceguisystem.hpp"

void Init_CeguiMouseCursor(VALUE rb_mCegui);
extern VALUE rb_mCeguiMouseCursor;



template <>
inline CEGUI::MouseCursor* wrap< CEGUI::MouseCursor* >(const VALUE &obj)
{
	wrap<CEGUI::System*>(Qnil);
	return CEGUI::MouseCursor::getSingletonPtr();
}

#endif /* __RubyCeguiMouseCursor_H__ */
