#ifndef __RubyCeguiItemListBase_H__
#define __RubyCeguiItemListBase_H__

#include "main.hpp"
void Init_CeguiItemListBase(VALUE rb_mCegui);
extern VALUE rb_cCeguiItemListBase;

#include "ceguimenubase.hpp"
#include "ceguiscrolleditemlistbase.hpp"

template <>
inline VALUE wrap< CEGUI::ItemListBase >(CEGUI::ItemListBase *itemlistbase )
{
	if(itemlistbase==NULL)
		return Qnil;
	CEGUI::MenuBase *menubase = dynamic_cast<CEGUI::MenuBase*>(itemlistbase);
	if(menubase)
		return wrap(menubase);
	CEGUI::ScrolledItemListBase *scrolleditemlistbase = dynamic_cast<CEGUI::ScrolledItemListBase*>(itemlistbase);
	if(scrolleditemlistbase)
		return wrap(scrolleditemlistbase);

	return RubyWindowHolder::get(itemlistbase,rb_cCeguiItemListBase);
}

template <>
inline CEGUI::ItemListBase* wrap< CEGUI::ItemListBase* >(const VALUE &vitemlistbase)
{
	if (rb_obj_is_kind_of(vitemlistbase, rb_cCeguiItemListBase)){
		return (CEGUI::ItemListBase*)wrap<CEGUI::Window*>(vitemlistbase);
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiItemListBase),rb_obj_classname(vitemlistbase));
		return NULL;
	}
}
#endif /* __RubyCeguiItemListBase_H__ */
