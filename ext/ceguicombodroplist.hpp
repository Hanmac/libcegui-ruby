#ifndef __RubyCeguiComboDropList_H__
#define __RubyCeguiComboDropList_H__

#include "main.hpp"
void Init_CeguiComboDropList(VALUE rb_mCegui);
extern VALUE rb_cCeguiComboDropList;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::ComboDropList >(CEGUI::ComboDropList *list )
{
	if(list==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(list);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = list;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiComboDropList, NULL, NULL, hold);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(list,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::ComboDropList* wrap< CEGUI::ComboDropList* >(const VALUE &vlist)
{
	if (rb_obj_is_kind_of(vlist, rb_cCeguiComboDropList)){
		return (CEGUI::ComboDropList*)(wrap< CEGUI::Window* >(vlist));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiComboDropList),rb_obj_classname(vlist));
		return NULL;
	}
}
#endif /* __RubyCeguiComboDropList_H__ */
