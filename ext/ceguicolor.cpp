#include "ceguicolor.hpp"
#include "ceguiexception.hpp"
#define _self wrap<CEGUI::Colour*>(self)
VALUE rb_cCeguiColor;

namespace CeguiColor
{

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::Colour);
}

macro_attr(Red,float)
macro_attr(Green,float)
macro_attr(Blue,float)
macro_attr(Alpha,float)

singlereturn(getHue)
singlereturn(getSaturation)
singlereturn(getLumination)

/*
 * call-seq:
 *   Color.new(red,green,blue[,alpha])
 * 
 * creates a new Color Object. 
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE red,green,blue,alpha;
	rb_scan_args(argc, argv, "31",&red,&green,&blue,&alpha);
	_setRed(self,red);
	_setGreen(self,green);
	_setBlue(self,blue);
	_setAlpha(self,NIL_P(alpha) ? DBL2NUM(1) : alpha);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_setRed(self,_getRed(other));
	_setGreen(self,_getGreen(other));
	_setBlue(self,_getBlue(other));
	_setAlpha(self,_getAlpha(other));
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
VALUE _inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_getRed(self);
	array[3]=_getGreen(self);
	array[4]=_getBlue(self);
	array[5]=_getAlpha(self);
	return rb_f_sprintf(6,array);
}

/*
 * call-seq:
 *   to_s -> String
 *
 * hexadecimal, #AARRGGBB
 * ===Return value
 * String
*/
VALUE _to_s(VALUE self)
{
	VALUE array[2];
	array[0]=rb_str_new2("%.8X");
	array[1]=LONG2NUM(_self->getARGB());
	return rb_f_sprintf(2,array);
}
/*
 *
 */
VALUE _equal(VALUE self,VALUE val)
{	if(self == val)
		return true;
	if(!is_wrapable<CEGUI::Colour>(val))
		return false;
	else
		return wrap(*_self == wrap<CEGUI::Colour>(val));
}
/*
 * call-seq:
 *   color + other_color -> new_color
 * 
 * adds the colors
 * ===Return value
 * Color
*/
VALUE _plus(VALUE self,VALUE val)
{
	return wrap(*_self + wrap<CEGUI::Colour>(val));
}
/*
 * call-seq:
 *   color - other_color -> new_color
 * 
 * minus the colors
 * ===Return value
 * Color
*/
VALUE _minus(VALUE self,VALUE val)
{
	return wrap(*_self - wrap<CEGUI::Colour>(val));
}
/*
 * call-seq:
 *   * Numeric -> new_color
 *
 * multipicate the colors
 * ===Return value
 * Color
*/
VALUE _mal(VALUE self,VALUE val)
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
VALUE _durch(VALUE self,VALUE val)
{
	return wrap(*_self * (float)(1.0 / NUM2DBL(val)));
}


/*
 * call-seq:
 *   marshal_dump -> string
 *
 * packs a ColorRect into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_getRed(self));
	rb_ary_push(result,_getGreen(self));
	rb_ary_push(result,_getBlue(self));
	rb_ary_push(result,_getAlpha(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 *
 * loads a string into an ColorRect.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	_setAlpha(self,rb_ary_pop(result));
	_setBlue(self,rb_ary_pop(result));
	_setGreen(self,rb_ary_pop(result));
	_setRed(self,rb_ary_pop(result));
	return self;
}

VALUE _setHue(VALUE self,VALUE val)
{
	_self->setHSL(NUM2DBL(val),
			_self->getSaturation(),
			_self->getLumination(),
			_self->getAlpha());
	return val;
}

VALUE _setSaturation(VALUE self,VALUE val)
{
	_self->setHSL(_self->getHue(),
			NUM2DBL(val),
			_self->getLumination(),
			_self->getAlpha());
	return val;
}

VALUE _setLumination(VALUE self,VALUE val)
{
	_self->setHSL(_self->getHue(),
			_self->getSaturation(),
			NUM2DBL(val),
			_self->getAlpha());
	return val;
}

}
/*
 * Document-class: CEGUI::Color
 * 
 * This class represents an Color. 
*/ 

/* Document-attr: red
 * returns the red value of Color. */
/* Document-attr: blue
 * returns the blue value of Color. */
/* Document-attr: green
 * returns the green value of Color. */
/* Document-attr: alpha
 * returns the alpha value of Color. */
/* Document-attr: hue
 * returns the hue value of Color. */
/* Document-attr: saturation
 * returns the saturation value of Color. */
/* Document-attr: lumination
 * returns the lumination value of Color. */
 
void Init_CeguiColor(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiColor,"red",1,1);
	rb_define_attr(rb_cCeguiColor,"blue",1,1);
	rb_define_attr(rb_cCeguiColor,"green",1,1);
	rb_define_attr(rb_cCeguiColor,"alpha",1,1);

	rb_define_attr(rb_cCeguiColor,"hue",1,1);
	rb_define_attr(rb_cCeguiColor,"saturation",1,1);
	rb_define_attr(rb_cCeguiColor,"lumination",1,1);
	
#endif

	using namespace CeguiColor;
	rb_cCeguiColor = rb_define_class_under(rb_mCegui,"Color",rb_cObject);
	rb_define_alloc_func(rb_cCeguiColor,_alloc);
	
	rb_define_method(rb_cCeguiColor,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cCeguiColor,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	

	rb_define_attr_method(rb_cCeguiColor,"red",_getRed,_setRed);
	rb_define_attr_method(rb_cCeguiColor,"blue",_getBlue,_setBlue);
	rb_define_attr_method(rb_cCeguiColor,"green",_getGreen,_setGreen);
	rb_define_attr_method(rb_cCeguiColor,"alpha",_getAlpha,_setAlpha);

	rb_define_attr_method(rb_cCeguiColor,"hue",_getHue,_setHue);
	rb_define_attr_method(rb_cCeguiColor,"saturation",_getSaturation,_setSaturation);
	rb_define_attr_method(rb_cCeguiColor,"lumination",_getLumination,_setLumination);

	rb_define_method(rb_cCeguiColor,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cCeguiColor,"to_s",RUBY_METHOD_FUNC(_to_s),0);

	rb_define_method(rb_cCeguiColor,"==",RUBY_METHOD_FUNC(_equal),1);

	rb_define_method(rb_cCeguiColor,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiColor,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);


	rb_define_method(rb_cCeguiColor,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cCeguiColor,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cCeguiColor,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cCeguiColor,"/",RUBY_METHOD_FUNC(_durch),1);
}

