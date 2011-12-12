#ifndef __RubyCeguiURect_H__
#define __RubyCeguiURect_H__

#include "main.hpp"
void Init_CeguiURect(VALUE rb_mCegui);
extern VALUE rb_cCeguiURect;

#include "ceguiuvector2.hpp"

template <>
inline VALUE wrap< CEGUI::URect >(CEGUI::URect *box )
{
	return Data_Wrap_Struct(rb_cCeguiURect, NULL, free, box);
}

template <>
inline CEGUI::URect* wrap< CEGUI::URect* >(const VALUE &vbox)
{
	if (rb_obj_is_kind_of(vbox, rb_cCeguiURect)){
		CEGUI::URect *box;
		Data_Get_Struct( vbox, CEGUI::URect, box);
		return box;
	}else if(rb_respond_to(vbox,rb_intern("min")) && 
	 rb_respond_to(vbox,rb_intern("max"))){
		CEGUI::URect *rect = new CEGUI::URect;
		rect->d_min = wrap<CEGUI::UVector2>(rb_funcall(vbox,rb_intern("min"),0));
		rect->d_max = wrap<CEGUI::UVector2>(rb_funcall(vbox,rb_intern("max"),0));
	 	return rect;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiURect),rb_obj_classname(vbox));
		return NULL;
	}

}
template <>
inline CEGUI::URect wrap< CEGUI::URect >(const VALUE &vbox)
{
	return *wrap< CEGUI::URect* >(vbox);
}
#endif /* __RubyCeguiURect_H__ */
