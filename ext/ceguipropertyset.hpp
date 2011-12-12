#ifndef __RubyCeguiPropertySet_H__
#define __RubyCeguiPropertySet_H__

#include "main.hpp"
#include "ceguiwindow.hpp"
#include "ceguifont.hpp"
void Init_CeguiPropertySet(VALUE rb_mCegui);
extern VALUE rb_mCeguiPropertySet;

extern std::map<VALUE,CEGUI::PropertySet*> propertysetholder;
template <>
inline VALUE wrap< CEGUI::PropertySet >(CEGUI::PropertySet* set)
{
	CEGUI::Window *window = dynamic_cast<CEGUI::Window*>(set);
	if(window)
		return wrap(window);
	CEGUI::Font *font = dynamic_cast<CEGUI::Font*>(set);
	if(font)
		return wrap(font);
	std::map<VALUE,CEGUI::PropertySet*>::iterator it;
	for(it = propertysetholder.begin();it != propertysetholder.end();++it)
	{
	if(it->second == set)
		return it->first;
	}
	return Qnil;
}

template <>
inline CEGUI::PropertySet* wrap< CEGUI::PropertySet* >(const VALUE &vset)
{
	if (rb_obj_is_kind_of(vset, rb_cCeguiWindow))
		return wrap< CEGUI::Window* >(vset);
	if (rb_obj_is_kind_of(vset, rb_cCeguiFont))
		return wrap< CEGUI::Font* >(vset);
	
	if (rb_obj_is_kind_of(vset, rb_mCeguiPropertySet)){
		std::map<VALUE,CEGUI::PropertySet*>::iterator it = propertysetholder.find(vset);
		if(it != propertysetholder.end()){
			return it->second;
		}else{
			CEGUI::PropertySet* temp = new CEGUI::PropertySet;
			propertysetholder.insert(std::make_pair(vset,temp));
			return temp;
		}
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_mCeguiPropertySet),rb_obj_classname(vset));
		return NULL;
	}
}
#endif /* __RubyCeguiPropertySet_H__ */
