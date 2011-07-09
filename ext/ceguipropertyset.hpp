#ifndef __RubyCeguiPropertySet_H__
#define __RubyCeguiPropertySet_H__

#include "main.hpp"
#include "ceguiwindow.hpp"
void Init_CeguiPropertySet(VALUE rb_mCegui);
extern VALUE rb_mCeguiPropertySet;

template <>
inline CEGUI::PropertySet* wrap< CEGUI::PropertySet* >(const VALUE &vset)
{
//	return wrap< CEGUI::Window* >(vwindow);
	
	if (rb_obj_is_kind_of(vset, rb_mCeguiPropertySet)){
		CEGUI::PropertySet *set;
		Data_Get_Struct( vset, CEGUI::PropertySet, set);
		return set;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_mCeguiPropertySet),rb_obj_classname(vset));
		return NULL;
	}
}
#endif /* __RubyCeguiPropertySet_H__ */
