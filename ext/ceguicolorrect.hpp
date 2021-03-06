#ifndef __RubyCeguiColorRect_H__
#define __RubyCeguiColorRect_H__

#include "main.hpp"
#include "ceguicolor.hpp"
void Init_CeguiColorRect(VALUE rb_mCegui);
extern VALUE rb_cCeguiColorRect;


template <>
inline VALUE wrap< CEGUI::ColourRect >(CEGUI::ColourRect *color )
{
	return Data_Wrap_Struct(rb_cCeguiColorRect, NULL, free, color);
}

template <>
inline bool is_wrapable< CEGUI::ColourRect >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cCeguiColorRect)){
		return true;
	}else if(rb_respond_to(vcolor,rb_intern("top_left")) &&
		rb_respond_to(vcolor,rb_intern("top_right")) &&
		rb_respond_to(vcolor,rb_intern("bottom_left")) &&
		rb_respond_to(vcolor,rb_intern("bottom_right"))){
		return true;
	}else
		return is_wrapable<CEGUI::Colour>(vcolor);
}


template <>
inline CEGUI::ColourRect* wrap< CEGUI::ColourRect* >(const VALUE &vcolor)
{
	if(NIL_P(vcolor))
		return new CEGUI::ColourRect(0XFFFFFFFF);
	if (rb_obj_is_kind_of(vcolor, rb_cCeguiColorRect)){
		CEGUI::ColourRect *color;
		Data_Get_Struct( vcolor, CEGUI::ColourRect, color);
		return color;
	}else if(rb_respond_to(vcolor,rb_intern("top_left")) && 
		rb_respond_to(vcolor,rb_intern("top_right")) &&
		rb_respond_to(vcolor,rb_intern("bottom_left")) &&
		rb_respond_to(vcolor,rb_intern("bottom_right"))){
		CEGUI::ColourRect *temp = new CEGUI::ColourRect;
		temp->d_top_left = wrap< CEGUI::Colour >(rb_funcall(vcolor,rb_intern("top_left"),0));
		temp->d_top_right = wrap< CEGUI::Colour >(rb_funcall(vcolor,rb_intern("top_right"),0));
		temp->d_bottom_left = wrap< CEGUI::Colour >(rb_funcall(vcolor,rb_intern("bottom_left"),0));
		temp->d_bottom_right = wrap< CEGUI::Colour >(rb_funcall(vcolor,rb_intern("bottom_right"),0));
		return temp;
	}else if (is_wrapable<CEGUI::Colour>(vcolor)){
		return new CEGUI::ColourRect(wrap< CEGUI::Colour >(vcolor));
	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiColorRect),rb_obj_classname(vcolor));
		return NULL;
	}
}
template <>
inline CEGUI::ColourRect wrap< CEGUI::ColourRect >(const VALUE &vcolor)
{
	return *wrap< CEGUI::ColourRect* >(vcolor);
}
#endif /* __RubyCeguiColor_H__ */
