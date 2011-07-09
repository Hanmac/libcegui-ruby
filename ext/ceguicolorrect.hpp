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
inline CEGUI::ColourRect* wrap< CEGUI::ColourRect* >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cCeguiColorRect)){
		CEGUI::ColourRect *color;
		Data_Get_Struct( vcolor, CEGUI::ColourRect, color);
		return color;
	}else if(rb_respond_to(vcolor,rb_intern("top_left")) && 
	 rb_respond_to(vcolor,rb_intern("top_right")) &&
	 rb_respond_to(vcolor,rb_intern("bottom_left")) &&
	 rb_respond_to(vcolor,rb_intern("bottom_right"))){
	 CEGUI::ColourRect *temp = new CEGUI::ColourRect;
	 temp->d_top_left = wrap< CEGUI::colour >(rb_funcall(vcolor,rb_intern("top_left"),0));
	 temp->d_top_right = wrap< CEGUI::colour >(rb_funcall(vcolor,rb_intern("top_right"),0));
	 temp->d_bottom_left = wrap< CEGUI::colour >(rb_funcall(vcolor,rb_intern("bottom_left"),0));
	 temp->d_bottom_right = wrap< CEGUI::colour >(rb_funcall(vcolor,rb_intern("bottom_right"),0));
	 return temp;
	}else if (rb_obj_is_kind_of(vcolor, rb_cCeguiColorRect) ||
	(rb_respond_to(vcolor,rb_intern("red")) && 
	 rb_respond_to(vcolor,rb_intern("blue")) &&
	 rb_respond_to(vcolor,rb_intern("green")) &&
	 rb_respond_to(vcolor,rb_intern("alpha")))){
		return new CEGUI::ColourRect(wrap< CEGUI::colour >(vcolor));
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiColorRect),rb_obj_classname(vcolor));
		return NULL;
	}
}
template <>
inline CEGUI::ColourRect wrap< CEGUI::ColourRect >(const VALUE &vcolor)
{
	return *wrap< CEGUI::ColourRect* >(vcolor);
}
#endif /* __RubyCeguiColor_H__ */
