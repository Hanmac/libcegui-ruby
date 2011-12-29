#include "ceguirenderedstringcomponent.hpp"

#define _self wrap<CEGUI::RenderedStringComponent*>(self)
VALUE rb_cCeguiRenderedStringComponent;
namespace CeguiRenderedStringComponent
{

macro_attr(VerticalFormatting,CEGUI::VerticalFormatting)

macro_attr(Padding,CEGUI::Rectf)
macro_attr(LeftPadding,float)
macro_attr(RightPadding,float)
macro_attr(TopPadding,float)
macro_attr(BottomPadding,float)

macro_attr(AspectLock,bool)



singlereturn(getPixelSize)
singlereturn(canSplit)

/*
*/
VALUE _draw(VALUE self,VALUE buffer,VALUE vec,VALUE color,VALUE rect,VALUE vertical_space,VALUE space_extra)
{

	_self->draw(*wrap< CEGUI::GeometryBuffer* >(buffer),
		wrap< CEGUI::Vector2f >(vec),wrap< CEGUI::ColourRect* >(color),
		wrap< CEGUI::Rectf* >(rect),NUM2DBL(vertical_space),NUM2DBL(space_extra));
	return self;
}

/*
*/
VALUE _split(VALUE self,VALUE split_point, VALUE first_component)
{
	return wrap(_self->split(NUM2DBL(split_point),NUM2DBL(first_component)));
}

}
/*
*/
void Init_CeguiRenderedStringComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiRenderedStringComponent,"verticalFormatting",1,1);

	rb_define_attr(rb_cCeguiRenderedStringComponent,"padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"left_padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"right_padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"top_padding",1,1);
	rb_define_attr(rb_cCeguiRenderedStringComponent,"bottom_padding",1,1);
	
	rb_define_attr(rb_cCeguiRenderedStringComponent,"aspect_lock",1,1);
	
#endif

	using namespace CeguiRenderedStringComponent;

	rb_cCeguiRenderedStringComponent = rb_define_class_under(rb_mCegui,"RenderedStringComponent",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderedStringComponent);


	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"verticalFormatting",_getVerticalFormatting,_setVerticalFormatting);

	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"padding",_getPadding,_setPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"left_padding",_getLeftPadding,_setLeftPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"right_padding",_getRightPadding,_setRightPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"top_padding",_getTopPadding,_setTopPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"bottom_padding",_getBottomPadding,_setBottomPadding);
	rb_define_attr_method(rb_cCeguiRenderedStringComponent,"aspect_lock",_getAspectLock,_setAspectLock);


	rb_define_method(rb_cCeguiRenderedStringComponent,"pixelSize",RUBY_METHOD_FUNC(_getPixelSize),0);
	rb_define_method(rb_cCeguiRenderedStringComponent,"splitable?",RUBY_METHOD_FUNC(_canSplit),0);


	rb_define_method(rb_cCeguiRenderedStringComponent,"split",RUBY_METHOD_FUNC(_split),2);
	rb_define_method(rb_cCeguiRenderedStringComponent,"draw",RUBY_METHOD_FUNC(_draw),6);
}
