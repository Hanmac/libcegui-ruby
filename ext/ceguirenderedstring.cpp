#include "ceguirenderedstring.hpp"
#include "ceguirenderedstringcomponent.hpp"
#define _self wrap<CEGUI::RenderedString*>(self)
VALUE rb_cCeguiRenderedString;


VALUE CeguiRenderedString_alloc(VALUE self)
{
	return wrap(new CEGUI::RenderedString);
}
/*
*/
VALUE CeguiRenderedString_getLineCount(VALUE self)
{
	return wrap(_self->getLineCount());
}
/*
*/
VALUE CeguiRenderedString_getComponentCount(VALUE self)
{
	return wrap(_self->getComponentCount());
}
/*
*/
VALUE CeguiRenderedString_getSpaceCount(VALUE self,VALUE line)
{
	return wrap(_self->getSpaceCount(NUM2ULONG(line)));
}



/*
*/
VALUE CeguiRenderedString_draw(VALUE self,VALUE line,VALUE buffer,VALUE vec,VALUE color,VALUE rect,VALUE space_extra)
{

	_self->draw(NUM2DBL(line),*wrap< CEGUI::GeometryBuffer* >(buffer),
		wrap< CEGUI::Vector2f >(vec),wrap< CEGUI::ColourRect* >(color),
		wrap< CEGUI::Rectf* >(rect),NUM2DBL(space_extra));
	return self;
}
/*
*/
void Init_CeguiRenderedString(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
#endif

	rb_cCeguiRenderedString = rb_define_class_under(rb_mCegui,"RenderedString",rb_cObject);
	rb_define_alloc_func(rb_cCeguiRenderedString,CeguiRenderedString_alloc);


	rb_define_method(rb_cCeguiRenderedString,"lineCount",
		RUBY_METHOD_FUNC(CeguiRenderedString_getLineCount),0);
	rb_define_method(rb_cCeguiRenderedString,"componentCount",
		RUBY_METHOD_FUNC(CeguiRenderedString_getComponentCount),0);
	rb_define_method(rb_cCeguiRenderedString,"spaceCount",
		RUBY_METHOD_FUNC(CeguiRenderedString_getSpaceCount),1);
	
	rb_define_method(rb_cCeguiRenderedString,"draw",RUBY_METHOD_FUNC(CeguiRenderedString_draw),6);
}
