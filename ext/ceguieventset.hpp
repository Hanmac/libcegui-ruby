#ifndef __RubyCeguiEventSet_H__
#define __RubyCeguiEventSet_H__

#include "main.hpp"
#include "ceguiwindow.hpp"
#include "ceguischeme.hpp"
#include "ceguifont.hpp"
//#include "ceguiimageset.hpp"
void Init_CeguiEventSet(VALUE rb_mCegui);
extern VALUE rb_mCeguiEventSet;

template <>
inline CEGUI::EventSet* wrap< CEGUI::EventSet* >(const VALUE &vset)
{
	if (rb_obj_is_kind_of(vset, rb_cCeguiWindow))
		return wrap< CEGUI::Window* >(vset);
	else if(vset == rb_cCeguiWindow)
		return CEGUI::WindowManager::getSingletonPtr();
	else if(vset == rb_cCeguiScheme)
		return CEGUI::SchemeManager::getSingletonPtr();
	else if(vset == rb_cCeguiFont)
		return CEGUI::FontManager::getSingletonPtr();
/*	
	if (rb_obj_is_kind_of(vset, rb_mCeguiEventSet)){
		CEGUI::EventSet *set;
		Data_Get_Struct( vset, CEGUI::EventSet, set);
		return set;
	}
*/
	else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_mCeguiEventSet),rb_obj_classname(vset));
		return NULL;
	}
}
#endif /* __RubyCeguiEventSet_H__ */
