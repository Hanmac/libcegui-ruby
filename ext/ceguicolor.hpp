#ifndef __RubyCeguiColor_H__
#define __RubyCeguiColor_H__

#include "main.hpp"
void Init_CeguiColor(VALUE rb_mCegui);
extern VALUE rb_cCeguiColor;


template <>
inline VALUE wrap< CEGUI::Colour >(CEGUI::Colour *color )
{
	return Data_Wrap_Struct(rb_cCeguiColor, NULL, free, color);
}

template <>
inline bool is_wrapable< CEGUI::Colour >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cCeguiColor)){
		return true;
	}else if(rb_respond_to(vcolor,rb_intern("red")) &&
		rb_respond_to(vcolor,rb_intern("blue")) &&
		rb_respond_to(vcolor,rb_intern("green")) &&
		rb_respond_to(vcolor,rb_intern("alpha"))){
		return true;
	}else
		return false;
}


template <>
inline CEGUI::Colour* wrap< CEGUI::Colour* >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cCeguiColor)){
		CEGUI::Colour *color;
		Data_Get_Struct( vcolor, CEGUI::Colour, color);
		return color;
	}else if(rb_respond_to(vcolor,rb_intern("red")) && 
	 rb_respond_to(vcolor,rb_intern("blue")) &&
	 rb_respond_to(vcolor,rb_intern("green")) &&
	 rb_respond_to(vcolor,rb_intern("alpha"))){
	 double temp;
	 CEGUI::Colour *color = new CEGUI::Colour;
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("red"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->setRed(temp);
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("blue"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->setBlue(temp);
	 
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("green"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->setGreen(temp);
	 
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("alpha"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->setAlpha(temp);
	 return color;
	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiColor),rb_obj_classname(vcolor));
		return NULL;
	}
}
template <>
inline CEGUI::Colour wrap< CEGUI::Colour >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cString)){
		return CEGUI::PropertyHelper<CEGUI::Colour>::fromString(wrap<CEGUI::String>(vcolor));
	}else
		return *wrap< CEGUI::Colour* >(vcolor);
}
#endif /* __RubyCeguiColor_H__ */
