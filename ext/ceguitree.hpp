#ifndef __RubyCeguiTree_H__
#define __RubyCeguiTree_H__

#include "main.hpp"
void Init_CeguiTree(VALUE rb_mCegui);
extern VALUE rb_cCeguiTree;

#include "ceguiwindowimpl.hpp"

template <>
inline VALUE wrap< CEGUI::Tree >(CEGUI::Tree *tree )
{
	return RubyWindowHolder::get(tree,rb_cCeguiTree);
}

template <>
inline CEGUI::Tree* wrap< CEGUI::Tree* >(const VALUE &vtree)
{
	if (rb_obj_is_kind_of(vtree, rb_cCeguiTree)){
		return (CEGUI::Tree*)(wrap< CEGUI::Window* >(vtree));
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiTree),rb_obj_classname(vtree));
		return NULL;
	}
}
#endif /* __RubyCeguiTree_H__ */
