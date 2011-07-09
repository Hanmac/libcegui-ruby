#ifndef __RubyCeguiColor_H__
#define __RubyCeguiColor_H__

#include "main.hpp"
void Init_CeguiColor(VALUE rb_mCegui);
extern VALUE rb_cCeguiColor;


template <>
inline VALUE wrap< CEGUI::colour >(CEGUI::colour *color )
{
	return Data_Wrap_Struct(rb_cCeguiColor, NULL, free, color);
}

template <>
inline CEGUI::colour* wrap< CEGUI::colour* >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cCeguiColor)){
		CEGUI::colour *color;
		Data_Get_Struct( vcolor, CEGUI::colour, color);
		return color;
	}else if(rb_respond_to(vcolor,rb_intern("red")) && 
	 rb_respond_to(vcolor,rb_intern("blue")) &&
	 rb_respond_to(vcolor,rb_intern("green")) &&
	 rb_respond_to(vcolor,rb_intern("alpha"))){
	 double temp;
	 CEGUI::colour *color = new CEGUI::colour;
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
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiColor),rb_obj_classname(vcolor));
		return NULL;
	}
}
template <>
inline CEGUI::colour wrap< CEGUI::colour >(const VALUE &vcolor)
{
	return *wrap< CEGUI::colour* >(vcolor);
}
#endif /* __RubyCeguiColor_H__ */
