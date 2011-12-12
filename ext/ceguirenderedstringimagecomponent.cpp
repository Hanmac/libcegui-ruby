#include "ceguirenderedstringimagecomponent.hpp"
#include "ceguirenderedstringcomponent.hpp"
#define _self wrap<CEGUI::RenderedStringImageComponent*>(self)
VALUE rb_cCeguiRenderedStringImageComponent;

namespace CeguiRenderedStringImageComponent {
	macro_attr(Image, CEGUI::Image*)
	macro_attr(Size, CEGUI::Sizef)
	macro_attr(Colours, CEGUI::ColourRect)

	VALUE _alloc(VALUE self)
	{
		return wrap(new CEGUI::RenderedStringImageComponent);
	}
}
/*
*/
void Init_CeguiRenderedStringImageComponent(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiRenderedStringImageComponent,"image",1,1);
	rb_define_attr(rb_cCeguiRenderedStringImageComponent,"size",1,1);
	rb_define_attr(rb_cCeguiRenderedStringImageComponent,"color",1,1);
	
	rb_cCeguiRenderedStringComponent = rb_define_class_under(rb_mCegui,"RenderedStringComponent",rb_cObject);
#endif

	using namespace CeguiRenderedStringImageComponent;
	rb_cCeguiRenderedStringImageComponent = rb_define_class_under(rb_mCegui,"RenderedStringImageComponent", rb_cCeguiRenderedStringComponent);
	rb_define_alloc_func(rb_cCeguiRenderedStringImageComponent,_alloc);

	rb_define_attr_method(rb_cCeguiRenderedStringImageComponent,"image",
		_getImage,_setImage);
	rb_define_attr_method(rb_cCeguiRenderedStringImageComponent,"size",
		_getSize,_setSize);
	rb_define_attr_method(rb_cCeguiRenderedStringImageComponent,"colors",
		_getColours,_setColours);
}
