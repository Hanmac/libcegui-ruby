#include "ceguicolor.hpp"

#define _self wrap<CEGUI::colour*>(self)
VALUE rb_cCeguiColor;

VALUE CeguiColor_alloc(VALUE self)
{
	return wrap(new CEGUI::colour);
}

macro_attr_with_func(Color,Red,DBL2NUM,NUM2DBL)
macro_attr_with_func(Color,Green,DBL2NUM,NUM2DBL)
macro_attr_with_func(Color,Blue,DBL2NUM,NUM2DBL)
macro_attr_with_func(Color,Alpha,DBL2NUM,NUM2DBL)
/*
 * call-seq:
 *   Color.new(red,green,blue[,alpha])
 * 
 * creates a new Color Object. 
*/
VALUE CeguiColor_initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE red,green,blue,alpha;
	rb_scan_args(argc, argv, "31",&red,&green,&blue,&alpha);
	CeguiColor_setRed(self,red);
	CeguiColor_setGreen(self,green);
	CeguiColor_setBlue(self,blue);
	if(!NIL_P(alpha))
		CeguiColor_setAlpha(self,alpha);
	return self;
}
/*
*/
VALUE CeguiColor_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiColor_setRed(self,CeguiColor_getRed(other));
	CeguiColor_setGreen(self,CeguiColor_getGreen(other));
	CeguiColor_setBlue(self,CeguiColor_getBlue(other));
	CeguiColor_setAlpha(self,CeguiColor_getAlpha(other));
	return result;
}
/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiColor_inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiColor_getRed(self);
	array[3]=CeguiColor_getGreen(self);
	array[4]=CeguiColor_getBlue(self);
	array[5]=CeguiColor_getAlpha(self);
	return rb_f_sprintf(6,array);
}

/*
 * call-seq:
 *   color + other_color -> new_color
 * 
 * adds the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_plus(VALUE self,VALUE val)
{
	return wrap(*_self + wrap<CEGUI::colour>(val));
}
/*
 * call-seq:
 *   color - other_color -> new_color
 * 
 * minus the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_minus(VALUE self,VALUE val)
{
	return wrap(*_self - wrap<CEGUI::colour>(val));
}
/*
 * call-seq:
 *   * Numeric -> new_color
 *
 * multipicate the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_mal(VALUE self,VALUE val)
{
	return wrap(*_self * (float)NUM2DBL(val));
}
/*
 * call-seq:
 *   color / Numeric -> new_color
 * 
 * devide the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_durch(VALUE self,VALUE val)
{
	return wrap(*_self * (float)(1.0 / NUM2DBL(val)));
}

/*
 * Document-class: CEGUI::Color
 * 
 * This class represents an Color. 
*/ 

/* Document-const: Zero
 * Color(0.0,0.0,0.0,0.0). */
/* Document-const: Black
 * Color(0.0,0.0,0.0,1.0). */
/* Document-const: White
 * Color(1.0,1.0,1.0,1.0). */
/* Document-const: Red
 * Color(1.0,0.0,0.0,1.0). */
/* Document-const: Green
 * Color(0.0,1.0,0.0,1.0). */
/* Document-const: Blue
 * Color(0.0,0.0,1.0,1.0). */
 
/* Document-attr: red
 * returns the red value of Color. */
/* Document-attr: blue
 * returns the blue value of Color. */
/* Document-attr: green
 * returns the green value of Color. */
/* Document-attr: alpha
 * returns the alpha value of Color. */
 
void Init_CeguiColor(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_define_attr(rb_cCeguiColor,"red",1,1);
	rb_define_attr(rb_cCeguiColor,"blue",1,1);
	rb_define_attr(rb_cCeguiColor,"green",1,1);
	rb_define_attr(rb_cCeguiColor,"alpha",1,1);

	rb_define_attr(rb_cCeguiColor,"hue",1,1);
	rb_define_attr(rb_cCeguiColor,"saturation",1,1);
	rb_define_attr(rb_cCeguiColor,"brightness",1,1);
	
#endif
	rb_cCeguiColor = rb_define_class_under(rb_mCegui,"Color",rb_cObject);
	rb_define_alloc_func(rb_cCeguiColor,CeguiColor_alloc);
	
	rb_define_method(rb_cCeguiColor,"initialize",RUBY_METHOD_FUNC(CeguiColor_initialize),-1);
	rb_define_private_method(rb_cCeguiColor,"initialize_copy",RUBY_METHOD_FUNC(CeguiColor_initialize_copy),1);
	

	rb_define_attr_method(rb_cCeguiColor,"red",CeguiColor_getRed,CeguiColor_setRed);
	rb_define_attr_method(rb_cCeguiColor,"blue",CeguiColor_getBlue,CeguiColor_setBlue);
	rb_define_attr_method(rb_cCeguiColor,"green",CeguiColor_getGreen,CeguiColor_setGreen);
	rb_define_attr_method(rb_cCeguiColor,"alpha",CeguiColor_getAlpha,CeguiColor_setAlpha);

	rb_define_method(rb_cCeguiColor,"inspect",RUBY_METHOD_FUNC(CeguiColor_inspect),0);
}

