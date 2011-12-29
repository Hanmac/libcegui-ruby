#include "ceguicolorrect.hpp"
#include "ceguivector2.hpp"
#include "ceguirect.hpp"
#define _self wrap<CEGUI::ColourRect*>(self)
VALUE rb_cCeguiColorRect;


namespace CeguiColorRect {
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::ColourRect);
}


macro_attr_prop(d_top_left,CEGUI::Colour)
macro_attr_prop(d_top_right,CEGUI::Colour)
macro_attr_prop(d_bottom_left,CEGUI::Colour)
macro_attr_prop(d_bottom_right,CEGUI::Colour)

VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE top_left,top_right,bottom_left,bottom_right;
	rb_scan_args(argc, argv, "13",&top_left,&top_right,&bottom_left,&bottom_right);
	if(argc == 1)
		_self->setColours(wrap<CEGUI::Colour>(top_left));
	else{
		_set_d_top_left(self,top_left);
		_set_d_top_right(self,top_right);
		_set_d_bottom_left(self,bottom_left);
		_set_d_bottom_right(self,bottom_right);
	}
	return self;
}
/*
 *
 */
VALUE _get(int argc,VALUE *argv,VALUE self)
{
	VALUE left,right,top,bottom;
	rb_scan_args(argc, argv, "13",&left,&right,&top,&bottom);
	if(argc > 2)
		return wrap(_self->getSubRectangle(NUM2DBL(left),NUM2DBL(right),NUM2DBL(top),NUM2DBL(bottom)));
	if(argc == 2)
		return wrap(_self->getColourAtPoint(NUM2DBL(left),NUM2DBL(right)));
	if(rb_respond_to(left,rb_intern("x")) && rb_respond_to(left,rb_intern("y"))){
		CEGUI::Vector2f *point = wrap<CEGUI::Vector2f*>(left);
		return wrap(_self->getColourAtPoint(point->d_x , point->d_y));
	}else{
		CEGUI::Rectf *rect = wrap<CEGUI::Rectf*>(left);
		return wrap(_self->getSubRectangle(rect->left(),rect->right(),rect->top(),rect->bottom()));
	}

}
/*
 *
 */
VALUE _equal(VALUE self,VALUE other)
{
	if(self == other)
		return Qtrue;
	if(!is_wrapable<CEGUI::ColourRect>(other))
		return Qfalse;
	if(_self->isMonochromatic() && is_wrapable<CEGUI::Colour>(other)){
		return wrap(_self->d_top_left == wrap<CEGUI::Colour>(other));
	}else{
		const CEGUI::ColourRect &cother = wrap<CEGUI::ColourRect>(other);
		return wrap(_self->d_top_left == cother.d_top_left &&
				_self->d_top_right == cother.d_top_right &&
				_self->d_bottom_left == cother.d_bottom_left &&
				_self->d_bottom_right == cother.d_bottom_right);
	}
}

VALUE _to_s(VALUE self)
{
	return wrap(CEGUI::PropertyHelper<CEGUI::ColourRect>::toString(*_self));
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
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:(%s)>");
	array[1]=rb_class_of(self);
	array[2]=_to_s(self);
	return rb_f_sprintf(3,array);
}
/*
 * call-seq:
 *   hash -> Integer
 *
 * hash from the combined  values.
 * ===Return value
 * Integer
*/
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();

	rb_ary_push(result,_get_d_top_left(self));
	rb_ary_push(result,_get_d_top_right(self));
	rb_ary_push(result,_get_d_bottom_left(self));
	rb_ary_push(result,_get_d_bottom_right(self));

	return rb_funcall(result,rb_intern("hash"),0);
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
	rb_ary_push(result,DBL2NUM(_self->d_top_left.getRed()));
	rb_ary_push(result,DBL2NUM(_self->d_top_left.getGreen()));
	rb_ary_push(result,DBL2NUM(_self->d_top_left.getBlue()));
	rb_ary_push(result,DBL2NUM(_self->d_top_left.getAlpha()));

	rb_ary_push(result,DBL2NUM(_self->d_top_right.getRed()));
	rb_ary_push(result,DBL2NUM(_self->d_top_right.getGreen()));
	rb_ary_push(result,DBL2NUM(_self->d_top_right.getBlue()));
	rb_ary_push(result,DBL2NUM(_self->d_top_right.getAlpha()));

	rb_ary_push(result,DBL2NUM(_self->d_bottom_left.getRed()));
	rb_ary_push(result,DBL2NUM(_self->d_bottom_left.getGreen()));
	rb_ary_push(result,DBL2NUM(_self->d_bottom_left.getBlue()));
	rb_ary_push(result,DBL2NUM(_self->d_bottom_left.getAlpha()));

	rb_ary_push(result,DBL2NUM(_self->d_bottom_right.getRed()));
	rb_ary_push(result,DBL2NUM(_self->d_bottom_right.getGreen()));
	rb_ary_push(result,DBL2NUM(_self->d_bottom_right.getBlue()));
	rb_ary_push(result,DBL2NUM(_self->d_bottom_right.getAlpha()));


	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 *
 * loads a string into an ColorRect.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	_self->d_bottom_right.setAlpha(NUM2DBL(rb_ary_pop(result)));
	_self->d_bottom_right.setBlue(NUM2DBL(rb_ary_pop(result)));
	_self->d_bottom_right.setGreen(NUM2DBL(rb_ary_pop(result)));
	_self->d_bottom_right.setRed(NUM2DBL(rb_ary_pop(result)));

	_self->d_bottom_left.setAlpha(NUM2DBL(rb_ary_pop(result)));
	_self->d_bottom_left.setBlue(NUM2DBL(rb_ary_pop(result)));
	_self->d_bottom_left.setGreen(NUM2DBL(rb_ary_pop(result)));
	_self->d_bottom_left.setRed(NUM2DBL(rb_ary_pop(result)));

	_self->d_top_right.setAlpha(NUM2DBL(rb_ary_pop(result)));
	_self->d_top_right.setBlue(NUM2DBL(rb_ary_pop(result)));
	_self->d_top_right.setGreen(NUM2DBL(rb_ary_pop(result)));
	_self->d_top_right.setRed(NUM2DBL(rb_ary_pop(result)));

	_self->d_top_left.setAlpha(NUM2DBL(rb_ary_pop(result)));
	_self->d_top_left.setBlue(NUM2DBL(rb_ary_pop(result)));
	_self->d_top_left.setGreen(NUM2DBL(rb_ary_pop(result)));
	_self->d_top_left.setRed(NUM2DBL(rb_ary_pop(result)));

	return self;
}

/*
*/
VALUE _swap(VALUE self,VALUE other)
{
	CEGUI::ColourRect* cother = wrap<CEGUI::ColourRect*>(other);

	std::swap(_self->d_top_left,cother->d_top_left);
	std::swap(_self->d_top_right,cother->d_top_right);
	std::swap(_self->d_bottom_left,cother->d_bottom_left);
	std::swap(_self->d_bottom_right,cother->d_bottom_right);

	return self;
}


}
/*
 * Document-class: CEGUI::ColorRect
 * 
 * 
*/ 
void Init_CeguiColorRect(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiColorRect,"top_left",1,1);
	rb_define_attr(rb_cCeguiColorRect,"top_right",1,1);
	rb_define_attr(rb_cCeguiColorRect,"bottom_left",1,1);
	rb_define_attr(rb_cCeguiColorRect,"bottom_right",1,1);

#endif
	using namespace CeguiColorRect;

	rb_cCeguiColorRect = rb_define_class_under(rb_mCegui,"ColorRect",rb_cObject);
	rb_define_alloc_func(rb_cCeguiColorRect,_alloc);

	rb_define_method(rb_cCeguiColorRect,"initialize",RUBY_METHOD_FUNC(_initialize),-1);

	
	rb_define_attr_method(rb_cCeguiColorRect,"top_left",_get_d_top_left,_set_d_top_left);
	rb_define_attr_method(rb_cCeguiColorRect,"top_right",_get_d_top_right,_set_d_top_right);
	rb_define_attr_method(rb_cCeguiColorRect,"bottom_left",_get_d_bottom_left,_set_d_bottom_left);
	rb_define_attr_method(rb_cCeguiColorRect,"bottom_right",_get_d_bottom_right,_set_d_bottom_right);

	rb_define_method(rb_cCeguiColorRect,"to_s",RUBY_METHOD_FUNC(_to_s),0);
	rb_define_method(rb_cCeguiColorRect,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cCeguiColorRect,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cCeguiColorRect,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cCeguiColorRect,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);

	rb_define_method(rb_cCeguiColorRect,"swap",RUBY_METHOD_FUNC(_swap),1);


	rb_define_method(rb_cCeguiColorRect,"[]",RUBY_METHOD_FUNC(_get),-1);
	rb_define_method(rb_cCeguiColorRect,"==",RUBY_METHOD_FUNC(_equal),1);

}
