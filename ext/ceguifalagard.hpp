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
	return unwrapPtr<CEGUI::WindowFactoryManager::FalagardWindowMapping>(vlook, rb_cCeguiFalagard);
}
#endif /* __RubyCeguiFalagard_H__ */
