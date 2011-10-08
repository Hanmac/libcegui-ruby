#include "ceguicolorrect.hpp"
#include "ceguirect.hpp"
#define _self wrap<CEGUI::ColourRect*>(self)
VALUE rb_cCeguiColorRect;

VALUE CeguiColorRect_alloc(VALUE self)
{
	return wrap(new CEGUI::ColourRect);
}
macro_attr_prop(ColorRect,d_top_left,CEGUI::Colour)
macro_attr_prop(ColorRect,d_top_right,CEGUI::Colour)
macro_attr_prop(ColorRect,d_bottom_left,CEGUI::Colour)
macro_attr_prop(ColorRect,d_bottom_right,CEGUI::Colour)

/*
 * Document-class: CEGUI::ColorRect
 * 
 * 
*/ 
void Init_CeguiColorRect(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiColorRect,"top_left",1,1);
	rb_define_attr(rb_cCeguiColorRect,"top_right",1,1);
	rb_define_attr(rb_cCeguiColorRect,"bottom_left",1,1);
	rb_define_attr(rb_cCeguiColorRect,"bottom_right",1,1);

#endif
	rb_cCeguiColorRect = rb_define_class_under(rb_mCegui,"ColorRect",rb_cObject);
	rb_define_alloc_func(rb_cCeguiColorRect,CeguiColorRect_alloc);
	
	rb_define_attr_method(rb_cCeguiColorRect,"top_left",CeguiColorRect_get_d_top_left,CeguiColorRect_set_d_top_left);
	rb_define_attr_method(rb_cCeguiColorRect,"top_right",CeguiColorRect_get_d_top_right,CeguiColorRect_set_d_top_right);
	rb_define_attr_method(rb_cCeguiColorRect,"bottom_left",CeguiColorRect_get_d_bottom_left,CeguiColorRect_set_d_bottom_left);
	rb_define_attr_method(rb_cCeguiColorRect,"bottom_right",CeguiColorRect_get_d_bottom_right,CeguiColorRect_set_d_bottom_right);
}
