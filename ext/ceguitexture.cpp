#include "ceguitexture.hpp"
#include "ceguisize.hpp"
#include "ceguivector2.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Texture*>(self)

VALUE rb_cCeguiTexture;


/*
*/
VALUE CeguiTexture_getSize(VALUE self)
{
	return wrap(_self->getSize());
}


/*
*/
VALUE CeguiTexture_getOriginalDataSize(VALUE self)
{
	return wrap(_self->getOriginalDataSize());
}

/*
*/
VALUE CeguiTexture_getTexelScaling(VALUE self)
{
	return wrap(_self->getTexelScaling());
}

/*
*/
VALUE CeguiTexture_load(VALUE self,VALUE path,VALUE group)
{
	_self->loadFromFile(wrap<CEGUI::String>(path),wrap<CEGUI::String>(group));
	return self;
}


/*
*/
void Init_CeguiTexture(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
#endif
	rb_cCeguiTexture = rb_define_class_under(rb_mCegui,"Texture",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiTexture);
	
	rb_define_method(rb_cCeguiTexture,"size",RUBY_METHOD_FUNC(CeguiTexture_getSize),0);
	rb_define_method(rb_cCeguiTexture,"originalDataSize",RUBY_METHOD_FUNC(CeguiTexture_getOriginalDataSize),0);
	rb_define_method(rb_cCeguiTexture,"texelScaling",RUBY_METHOD_FUNC(CeguiTexture_getTexelScaling),0);	

	rb_define_method(rb_cCeguiTexture,"load",RUBY_METHOD_FUNC(CeguiTexture_load),2);

}
