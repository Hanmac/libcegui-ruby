#ifndef __RubyCeguiTree_H__
#define __RubyCeguiTree_H__

#include "main.hpp"
void Init_CeguiTree(VALUE rb_mCegui);
extern VALUE rb_cCeguiTree;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Tree >(CEGUI::Tree *tree )
{
	if(tree==NULL)
		return Qnil;
	std::map<CEGUI::Window*,RubyWindowHolder*>::iterator it = rubywindowholder.find(tree);
	if(it != rubywindowholder.end()){
		return it->second->ruby;
	}else{
		RubyWindowHolder* hold = new RubyWindowHolder;
		hold->window = tree;
		hold->ruby = Data_Wrap_Struct(rb_cCeguiTree, NULL, NULL, hold);
		rb_ary_push(rb_windowholder,hold->ruby);
		rubywindowholder.insert(std::pair<CEGUI::Window*,RubyWindowHolder*>(tree,hold));
		return hold->ruby;
	}
}

template <>
inline CEGUI::Tree* wrap< CEGUI::Tree* >(const VALUE &vtree)
{
	if (rb_obj_is_kind_of(vtree, rb_cCeguiTree)){
		return (CEGUI::Tree*)(wrap< CEGUI::Window* >(vtree));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiTree),rb_obj_classname(vtree));
		return NULL;
	}
}
#endif /* __RubyCeguiTree_H__ */
