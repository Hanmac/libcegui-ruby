#include "ceguirenderedstringcomponent.hpp"

#define _self wrap<CEGUI::RenderedStringComponent*>(self)
VALUE rb_cCeguiRenderedStringComponent;

macro_attr(RenderedStringComponent,Padding,CEGUI::Rectf)
macro_attr(RenderedStringComponent,LeftPadding,float)
macro_attr(RenderedStringComponent,RightPadding,float)
macro_attr(RenderedStringComponent,TopPadding,float)
macro_attr(RenderedStringComponent,BottomPadding,float)

macro_attr(RenderedStringComponent,AspectLock,bool)
/*
*/
VALUE CeguiRenderedStringComponent_canSplit(VALUE self)
{
	return wrap(_self->canSplit());
}
/*
*/
VALUE CeguiRenderedStringComponent_draw(VALUE self,VALUE buffer,VALUE vec,VALUE color,VALUE rect,VALUE vertical_space,VALUE space_extra)
{

	_self->draw(*wrap< CEGUI::GeometryBuffer* >(buffer),
		wrap< CEGUI::Vector2f >(vec),wrap< CEGUI::ColourRect* >(color),
		wrap< CEGUI::Rectf* >(rect),NUM2DBL(vertical_space),NUM2DBL(space_extra));
	return self;
}

/*
*/
VALUE CeguiRenderedStringComponent_split(VALUE self,VALUE split_point, VALUE first_component)
{
	return wrap(_self->split(NUM2DBL(split_point),NUM2DBL(first_component)));
}
/*
*/
void Init_CeguiRenderedStringComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_define_attr(rb_cCeguiRenderedStringComponent,"padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"left_padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"right_padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"top_padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"bottom_padding",1,1);
	
	rb_define_attr(rb_cCeguiRenderedStringComponent,"aspect_lock",1,1);
	
#endif

	rb_cCeguiRenderedStringComponent = rb_define_class_under(rb_mCegui,"RenderedStringComponent",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderedStringComponent);

	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"padding",
		CeguiRenderedStringComponent_getPadding,CeguiRenderedStringComponent_setPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"left_padding",
		CeguiRenderedStringComponent_getLeftPadding,CeguiRenderedStringComponent_setLeftPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"right_padding",
		CeguiRenderedStringComponent_getRightPadding,CeguiRenderedStringComponent_setRightPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"top_padding",
		CeguiRenderedStringComponent_getTopPadding,CeguiRenderedStringComponent_setTopPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"bottom_padding",
		CeguiRenderedStringComponent_getBottomPadding,CeguiRenderedStringComponent_setBottomPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"aspect_lock",
		CeguiRenderedStringComponent_getAspectLock,CeguiRenderedStringComponent_setAspectLock);


	rb_define_method(rb_cCeguiRenderedStringComponent,"splitable?",RUBY_METHOD_FUNC(CeguiRenderedStringComponent_canSplit),0);
	rb_define_method(rb_cCeguiRenderedStringComponent,"split",RUBY_METHOD_FUNC(CeguiRenderedStringComponent_split),2);
	rb_define_method(rb_cCeguiRenderedStringComponent,"draw",RUBY_METHOD_FUNC(CeguiRenderedStringComponent_draw),6);
}
