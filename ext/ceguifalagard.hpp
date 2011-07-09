#ifndef __RubyCeguiFalagard_H__
#define __RubyCeguiFalagard_H__

#include "main.hpp"
void Init_CeguiFalagard(VALUE rb_mCegui);
extern VALUE rb_cCeguiFalagard;

template <>
inline VALUE wrap< CEGUI::WindowFactoryManager::FalagardWindowMapping >(CEGUI::WindowFactoryManager::FalagardWindowMapping *look )
{
	if(look==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiFalagard, NULL, free, look);
}
template <>
inline CEGUI::WindowFactoryManager::FalagardWindowMapping* wrap< CEGUI::WindowFactoryManager::FalagardWindowMapping* >(const VALUE &vlook)
{
	if (rb_obj_is_kind_of(vlook, rb_cCeguiFalagard)){
		CEGUI::WindowFactoryManager::FalagardWindowMapping *look;
		Data_Get_Struct( vlook, CEGUI::WindowFactoryManager::FalagardWindowMapping, look);
		return look;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiFalagard),rb_obj_classname(vlook));
		return NULL;
	}
}
#endif /* __RubyCeguiFalagard_H__ */
