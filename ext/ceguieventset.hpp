#ifndef __RubyCeguiEventSet_H__
#define __RubyCeguiEventSet_H__

#include "main.hpp"
#include "ceguiwindow.hpp"
#include "ceguischeme.hpp"
#include "ceguifont.hpp"
#include "ceguisystem.hpp"
//#include "ceguiimageset.hpp"
void Init_CeguiEventSet(VALUE rb_mCegui);
extern VALUE rb_mCeguiEventSet;

extern std::map<VALUE,CEGUI::EventSet*> eventsetholder;

template <>
inline VALUE wrap< CEGUI::EventSet >(CEGUI::EventSet *set)
{
	CEGUI::Window *window = dynamic_cast<CEGUI::Window*>(set);
	if(window)
		return wrap(window);
	std::map<VALUE,CEGUI::EventSet*>::iterator it;
	for(it = eventsetholder.begin();it != eventsetholder.end();++it)
	{
	if(it->second == set)
		return it->first;
	}
	return Qnil;
}

template <>
inline CEGUI::EventSet* wrap< CEGUI::EventSet* >(const VALUE &vset)
{
	CEGUI::EventSet* result;
	if (rb_obj_is_kind_of(vset, rb_cCeguiWindow))
		result = wrap< CEGUI::Window* >(vset);
	else if(vset == rb_cCeguiWindow)
		result = CEGUI::WindowManager::getSingletonPtr();
	else if(vset == rb_cCeguiScheme)
		result = CEGUI::SchemeManager::getSingletonPtr();
	else if(vset == rb_cCeguiFont)
		result = CEGUI::FontManager::getSingletonPtr();
	else if(vset == rb_mCeguiSystem)
		result = CEGUI::System::getSingletonPtr();
	else if (rb_obj_is_kind_of(vset, rb_mCeguiEventSet)){
		std::map<VALUE,CEGUI::EventSet*>::iterator it = eventsetholder.find(vset);
		if(it != eventsetholder.end()){
			return it->second;
		}else{
			CEGUI::EventSet* temp = new CEGUI::EventSet;
			eventsetholder.insert(std::make_pair(vset,temp));
			return temp;
		}
	}
	else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_mCeguiEventSet),rb_obj_classname(vset));
		return NULL;
	}
	
	if(result == NULL)
		rb_raise(rb_eRuntimeError,"%s is not created!",rb_class2name(rb_mCeguiSystem));
	return result;
	
}
#endif /* __RubyCeguiEventSet_H__ */
