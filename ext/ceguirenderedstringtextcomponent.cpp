#include "ceguirenderedstringtextcomponent.hpp"
#include "ceguirenderedstringcomponent.hpp"
#define _self wrap<CEGUI::RenderedStringTextComponent*>(self)
VALUE rb_cCeguiRenderedStringTextComponent;

macro_attr(RenderedStringTextComponent,Text ,CEGUI::String)
macro_attr(RenderedStringTextComponent,Font ,CEGUI::Font*)
macro_attr(RenderedStringTextComponent,Colours ,CEGUI::ColourRect)

VALUE CeguiRenderedStringTextComponent_alloc(VALUE self)
{
	return wrap(new CEGUI::RenderedStringTextComponent);
}
/*
*/
void Init_CeguiRenderedStringTextComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_define_attr(rb_cCeguiRenderedStringTextComponent,"text",1,1);
	rb_define_attr(rb_cCeguiRenderedStringTextComponent,"font",1,1);
	rb_define_attr(rb_cCeguiRenderedStringTextComponent,"color",1,1);
	
	rb_cCeguiRenderedStringComponent = rb_define_class_under(rb_mCegui,"RenderedStringComponent",rb_cObject);
#endif

	rb_cCeguiRenderedStringTextComponent = rb_define_class_under(rb_mCegui,"RenderedStringTextComponent", rb_cCeguiRenderedStringComponent);
	rb_define_alloc_func(rb_cCeguiRenderedStringTextComponent,CeguiRenderedStringTextComponent_alloc);

	rb_define_attr_method(rb_cCeguiRenderedStringTextComponent,"text",
		CeguiRenderedStringTextComponent_getText,CeguiRenderedStringTextComponent_setText);
	rb_define_attr_method(rb_cCeguiRenderedStringTextComponent,"font",
		CeguiRenderedStringTextComponent_getFont,CeguiRenderedStringTextComponent_setFont);
	rb_define_attr_method(rb_cCeguiRenderedStringTextComponent,"colors",
		CeguiRenderedStringTextComponent_getColours,CeguiRenderedStringTextComponent_setColours);
}
