/*
 * ceguiaffector.hpp
 *
 *  Created on: 12.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiAffector_H__
#define __RubyCeguiAffector_H__

#include "main.hpp"
#include "ceguiexception.hpp"
void Init_CeguiAffector(VALUE rb_mCegui);
extern VALUE rb_cCeguiAffector;

template <>
inline VALUE wrap< CEGUI::Affector >(CEGUI::Affector *affector )
{
	if(affector==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiAffector, NULL, NULL, affector);
}
template <>
inline CEGUI::Affector* wrap< CEGUI::Affector* >(const VALUE &vaffector)
{
	return unwrapPtr<CEGUI::Affector>(vaffector, rb_cCeguiAffector);
}
#endif /* __RubyCeguiAffector_H__ */

