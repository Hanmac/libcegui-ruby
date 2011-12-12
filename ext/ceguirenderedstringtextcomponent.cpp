#include "ceguirenderedstringtextcomponent.hpp"
#include "ceguirenderedstringcomponent.hpp"
#define _self wrap<CEGUI::RenderedStringTextComponent*>(self)
VALUE rb_cCeguiRenderedStringTextComponent;

namespace CeguiRenderedStringTextComponent {

macro_attr(Text, CEGUI::String)
macro_attr(Font, CEGUI::Font*)
macro_attr(Colours, CEGUI::ColourRect)

VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::RenderedStringTextComponent);
}

}
/*
*/
void Init_CeguiRenderedStringTextComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiRenderedStringTextComponent,"text",1,1);
	rb_define_attr(rb_cCeguiRenderedStringTextComponent,"font",1,1);
	rb_define_attr(rb_cCeguiRenderedStringTextComponent,"color",1,1);
	
	rb_cCeguiRenderedStringComponent = rb_define_class_under(rb_mCegui,"RenderedStringComponent",rb_cObject);
#endif
	using namespace CeguiRenderedStringTextComponent;

	rb_cCeguiRenderedStringTextComponent = rb_define_class_under(rb_mCegui,"RenderedStringTextComponent", rb_cCeguiRenderedStringComponent);
	rb_define_alloc_func(rb_cCeguiRenderedStringTextComponent,_alloc);

	rb_define_attr_method(rb_cCeguiRenderedStringTextComponent,"text",_getText,_setText);
	rb_define_attr_method(rb_cCeguiRenderedStringTextComponent,"font",_getFont,_setFont);
	rb_define_attr_method(rb_cCeguiRenderedStringTextComponent,"colors",_getColours,_setColours);
}
