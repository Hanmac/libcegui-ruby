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
	return unwrapWindow<CEGUI::Tree>(vtree, rb_cCeguiTree);
}
#endif /* __RubyCeguiTree_H__ */
