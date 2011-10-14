#include "ceguirenderedstringimagecomponent.hpp"
#include "ceguirenderedstringcomponent.hpp"
#define _self wrap<CEGUI::RenderedStringImageComponent*>(self)
VALUE rb_cCeguiRenderedStringImageComponent;

macro_attr(RenderedStringImageComponent,Image ,CEGUI::Image*)
macro_attr(RenderedStringImageComponent,Size ,CEGUI::Sizef)
macro_attr(RenderedStringImageComponent,Colours ,CEGUI::ColourRect)

VALUE CeguiRenderedStringImageComponent_alloc(VALUE self)
{
	return wrap(new CEGUI::RenderedStringImageComponent);
}
/*
*/
void Init_CeguiRenderedStringImageComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	
	rb_define_attr(rb_cCeguiRenderedStringImageComponent,"image",1,1);
	rb_define_attr(rb_cCeguiRenderedStringImageComponent,"size",1,1);
	rb_define_attr(rb_cCeguiRenderedStringImageComponent,"color",1,1);
	
	rb_cCeguiRenderedStringComponent = rb_define_class_under(rb_mCegui,"RenderedStringComponent",rb_cObject);
#endif

	rb_cCeguiRenderedStringImageComponent = rb_define_class_under(rb_mCegui,"RenderedStringImageComponent", rb_cCeguiRenderedStringComponent);
	rb_define_alloc_func(rb_cCeguiRenderedStringImageComponent,CeguiRenderedStringImageComponent_alloc);

	rb_define_attr_method(rb_cCeguiRenderedStringImageComponent,"image",
		CeguiRenderedStringImageComponent_getImage,CeguiRenderedStringImageComponent_setImage);
	rb_define_attr_method(rb_cCeguiRenderedStringImageComponent,"size",
		CeguiRenderedStringImageComponent_getSize,CeguiRenderedStringImageComponent_setSize);
	rb_define_attr_method(rb_cCeguiRenderedStringImageComponent,"colors",
		CeguiRenderedStringImageComponent_getColours,CeguiRenderedStringImageComponent_setColours);
}
