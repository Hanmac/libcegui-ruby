#include "ceguirenderedstring.hpp"
#include "ceguirenderedstringcomponent.hpp"
#define _self wrap<CEGUI::RenderedString*>(self)
VALUE rb_cCeguiRenderedString;

namespace CeguiRenderedString {

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::RenderedString);
}
/*
*/
VALUE _getLineCount(VALUE self)
{
	return wrap(_self->getLineCount());
}
/*
*/
VALUE _getComponentCount(VALUE self)
{
	return wrap(_self->getComponentCount());
}
/*
*/
VALUE _getSpaceCount(VALUE self,VALUE line)
{
	return wrap(_self->getSpaceCount(NUM2ULONG(line)));
}
/*
*/
VALUE _append(VALUE self,VALUE component)
{
	_self->appendComponent(*wrap< CEGUI::RenderedStringComponent* >(component));
	return self;
}
/*
*/
VALUE _split(VALUE self,VALUE line, VALUE split_point)
{
	CEGUI::RenderedString *temp = new CEGUI::RenderedString;
	try{
		_self->split(NUM2ULONG(line),NUM2DBL(split_point),*temp);
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return wrap(temp);
}
/*
*/
VALUE _draw(VALUE self,VALUE line,VALUE buffer,VALUE vec,VALUE color,VALUE rect,VALUE space_extra)
{
	try {
	_self->draw(NUM2DBL(line),*wrap< CEGUI::GeometryBuffer* >(buffer),
		wrap< CEGUI::Vector2f >(vec),wrap< CEGUI::ColourRect* >(color),
		wrap< CEGUI::Rectf* >(rect),NUM2DBL(space_extra));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}

}

/*
*/
void Init_CeguiRenderedString(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif
	using namespace CeguiRenderedString;

	rb_cCeguiRenderedString = rb_define_class_under(rb_mCegui,"RenderedString",rb_cObject);
	rb_define_alloc_func(rb_cCeguiRenderedString,_alloc);


	rb_define_method(rb_cCeguiRenderedString,"lineCount",RUBY_METHOD_FUNC(_getLineCount),0);
	rb_define_method(rb_cCeguiRenderedString,"componentCount",RUBY_METHOD_FUNC(_getComponentCount),0);
	rb_define_method(rb_cCeguiRenderedString,"spaceCount",RUBY_METHOD_FUNC(_getSpaceCount),1);
	
	rb_define_method(rb_cCeguiRenderedString,"<<",RUBY_METHOD_FUNC(_append),1);
	rb_define_method(rb_cCeguiRenderedString,"split",RUBY_METHOD_FUNC(_split),2);

	rb_define_method(rb_cCeguiRenderedString,"draw",RUBY_METHOD_FUNC(_draw),6);
}
