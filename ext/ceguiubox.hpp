#ifndef __RubyCeguiUBox_H__
#define __RubyCeguiUBox_H__

#include "main.hpp"
void Init_CeguiUBox(VALUE rb_mCegui);
extern VALUE rb_cCeguiUBox;

#include "ceguiudim.hpp"

template <>
inline VALUE wrap< CEGUI::UBox >(CEGUI::UBox *box )
{
	return Data_Wrap_Struct(rb_cCeguiUBox, NULL, free, box);
}

template <>
inline CEGUI::UBox* wrap< CEGUI::UBox* >(const VALUE &vbox)
{
	if (rb_obj_is_kind_of(vbox, rb_cCeguiUBox)){
		CEGUI::UBox *box;
		Data_Get_Struct( vbox, CEGUI::UBox, box);
		return box;
	}else if(rb_respond_to(vbox,rb_intern("top")) && 
	 rb_respond_to(vbox,rb_intern("left")) && 
	 rb_respond_to(vbox,rb_intern("bottom")) && 
	 rb_respond_to(vbox,rb_intern("right"))){
		CEGUI::UBox *box = new CEGUI::UBox;
		box->d_top = wrap<CEGUI::UDim>(rb_funcall(vbox,rb_intern("top"),0));
		box->d_left = wrap<CEGUI::UDim>(rb_funcall(vbox,rb_intern("left"),0));
		box->d_bottom = wrap<CEGUI::UDim>(rb_funcall(vbox,rb_intern("bottom"),0));
		box->d_right = wrap<CEGUI::UDim>(rb_funcall(vbox,rb_intern("right"),0));
	 	return box;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiUBox),rb_obj_classname(vbox));
		return NULL;
	}

}
template <>
inline CEGUI::UBox wrap< CEGUI::UBox >(const VALUE &vbox)
{
	return *wrap< CEGUI::UBox* >(vbox);
}
#endif /* __RubyCeguiUBox_H__ */
