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
	try {
		if (rb_obj_is_kind_of(vaffector, rb_cCeguiAffector)){
			CEGUI::Affector *affector;
			Data_Get_Struct( vaffector, CEGUI::Affector, affector);
			return affector;
		}else{
			rb_raise(rb_eTypeError,"Excepted %s got %s!",
				rb_class2name(rb_cCeguiAffector),rb_obj_classname(vaffector));
			return NULL;
		}
	}catch(CEGUI::Exception& e){
		rb_raise(e);
		return NULL;
	}
}
#endif /* __RubyCeguiAffector_H__ */

