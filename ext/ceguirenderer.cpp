#include "ceguirenderer.hpp"

#include "ceguisize.hpp"
#include "ceguitexture.hpp"
#include "ceguitexturetarget.hpp"
#include "ceguigeometrybuffer.hpp"
#include "ceguiexception.hpp"
#include "ceguiwindowimpl.hpp"

#include "ceguisystem.hpp"

#define _self wrap<CEGUI::Renderer*>(self)
VALUE rb_cCeguiRenderer;

namespace CeguiRenderer {

macro_attr(DisplaySize,CEGUI::Sizef)
singlefunc(beginRendering)
singlefunc(endRendering)

singlereturn(getIdentifierString)
singlereturn(createGeometryBuffer)
singlereturn(createTextureTarget)

/*
*/
VALUE _createTexture(int argc,VALUE *argv,VALUE self)
{
	VALUE name,obj,resource_group;
	rb_scan_args(argc, argv, "12",&name,&obj,&resource_group);
	if(argc==1)
		return wrap(_self->createTexture(wrap<CEGUI::String>(name)));
	else if(argc==2)
		return wrap(_self->createTexture(wrap<CEGUI::String>(name),wrap<CEGUI::Sizef>(obj)));
	else
		return wrap(_self->createTexture(wrap<CEGUI::String>(name),wrap<CEGUI::String>(obj),wrap<CEGUI::String>(resource_group)));
}

/*
 * call-seq:
 *   inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[2];
	array[0]=rb_str_new2("#<%s>");
	array[1]=rb_funcall(self,"name");
	return rb_f_sprintf(2,array);
}

}

#if HAVE_CEGUI_RENDERERMODULES_OPENGL_RENDERER_H
VALUE rb_cCeguiOpenGLRenderer;
namespace CeguiRenderer {

/*
*/
VALUE _opengl_bootstrap(VALUE self)
{
	try {
		VALUE val = wrap(CEGUI::OpenGLRenderer::bootstrapSystem());
		ruby_bootstrap();
		return val;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _opengl_alloc(VALUE self)
{
	try {
		return wrap(CEGUI::OpenGLRenderer::create());
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
}
#endif


#if HAVE_CEGUI_RENDERERMODULES_OPENGLES_RENDERER_H
VALUE rb_cCeguiOpenGLESRenderer;
namespace CeguiRenderer {

/*
*/
VALUE _opengles_bootstrap(VALUE self)
{
	try {
		VALUE val = wrap(CEGUI::OpenGLESRenderer::bootstrapSystem());
		ruby_bootstrap();
		return val;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _opengles_alloc(VALUE self)
{
	try {
		return wrap(CEGUI::OpenGLESRenderer::create());
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
}
#endif
#if HAVE_CEGUI_RENDERERMODULES_NULL_RENDERER_H
VALUE rb_cCeguiNullRenderer;
namespace CeguiRenderer {
/*
*/
VALUE _null_bootstrap(VALUE self)
{
	try {
		VALUE val = wrap(CEGUI::NullRenderer::bootstrapSystem());
		ruby_bootstrap();
		return val;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _null_alloc(VALUE self)
{
	try {
		return wrap(CEGUI::NullRenderer::create());
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
}
#endif
#if HAVE_CEGUI_RENDERERMODULES_OGRE_RENDERER_H
VALUE rb_cCeguiOgreRenderer;
namespace CeguiRenderer {
/*
*/
VALUE _ogre_bootstrap(VALUE self)
{
	try {
		VALUE val = wrap(CEGUI::OgreRenderer::bootstrapSystem());
		ruby_bootstrap();
		return val;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _ogre_alloc(VALUE self)
{
	try {
		return wrap(CEGUI::OgreRenderer::create());
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
}
#endif

#if HAVE_CEGUI_RENDERERMODULES_IRRLICHT_RENDERER_H
VALUE rb_cCeguiIrrlichtRenderer;
namespace CeguiRenderer {

/*
*/
VALUE _irrlicht_bootstrap(VALUE self,VALUE irr)
{
	try {
		irr::IrrlichtDevice *obj = wrap<irr::IrrlichtDevice*>(irr);
		VALUE val = wrap(CEGUI::IrrlichtRenderer::bootstrapSystem(*obj));
		ruby_bootstrap();
		return val;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _irrlicht_alloc(VALUE self,VALUE irr)
{
	try {
		irr::IrrlichtDevice *obj = wrap<irr::IrrlichtDevice*>(irr);
		return wrap(CEGUI::IrrlichtRenderer::create(*obj));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
}
#endif

/* Document-method: beginRendering
*/

/* Document-method: endRendering
*/

/* Document-method: name
*/
/* Document-method: createGeometryBuffer
*/
/* Document-method: createTextureTarget
*/



void Init_CeguiRenderer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	rb_define_attr(rb_cCeguiRenderer,"displaySize",1,1);
#endif
	using namespace CeguiRenderer;

	rb_cCeguiRenderer = rb_define_class_under(rb_mCegui,"Renderer",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiRenderer);
	
	rb_define_attr_method(rb_cCeguiRenderer,"displaySize",_getDisplaySize,_setDisplaySize);

	rb_define_method(rb_cCeguiRenderer,"inspect",RUBY_METHOD_FUNC(_inspect),0);
	rb_define_method(rb_cCeguiRenderer,"name",RUBY_METHOD_FUNC(_getIdentifierString),0);

	rb_define_method(rb_cCeguiRenderer,"beginRendering",RUBY_METHOD_FUNC(_beginRendering),0);
	rb_define_method(rb_cCeguiRenderer,"endRendering",RUBY_METHOD_FUNC(_endRendering),0);

	rb_define_method(rb_cCeguiRenderer,"createGeometryBuffer",RUBY_METHOD_FUNC(_createGeometryBuffer),0);
	rb_define_method(rb_cCeguiRenderer,"createTexture",RUBY_METHOD_FUNC(_createTexture),-1);
	rb_define_method(rb_cCeguiRenderer,"createTextureTarget",RUBY_METHOD_FUNC(_createTextureTarget),0);


#if HAVE_CEGUI_RENDERERMODULES_NULL_RENDERER_H
	rb_cCeguiNullRenderer = rb_define_class_under(rb_mCegui,"NullRenderer",rb_cCeguiRenderer);
	rb_define_alloc_func(rb_cCeguiNullRenderer,_null_alloc);
	rb_define_singleton_method(rb_cCeguiNullRenderer,"bootstrap",RUBY_METHOD_FUNC(_null_bootstrap),0);
#endif

#if HAVE_CEGUI_RENDERERMODULES_OPENGL_RENDERER_H
	rb_cCeguiOpenGLRenderer = rb_define_class_under(rb_mCegui,"OpenGLRenderer",rb_cCeguiRenderer);
	rb_define_alloc_func(rb_cCeguiOpenGLRenderer,_opengl_alloc);
	rb_define_singleton_method(rb_cCeguiOpenGLRenderer,"bootstrap",RUBY_METHOD_FUNC(_opengl_bootstrap),0);
#endif

#if HAVE_CEGUI_RENDERERMODULES_OPENGLES_RENDERER_H
	rb_cCeguiOpenGLESRenderer = rb_define_class_under(rb_mCegui,"OpenGLESRenderer",rb_cCeguiRenderer);
	rb_define_alloc_func(rb_cCeguiOpenGLESRenderer,_opengles_alloc);
	rb_define_singleton_method(rb_cCeguiOpenGLESRenderer,"bootstrap",RUBY_METHOD_FUNC(_opengles_bootstrap),0);
#endif

#if HAVE_CEGUI_RENDERERMODULES_OGRE_RENDERER_H
	rb_cCeguiOgreRenderer = rb_define_class_under(rb_mCegui,"OgreRenderer",rb_cCeguiRenderer);
	rb_define_alloc_func(rb_cCeguiOgreRenderer,_ogre_alloc);
	rb_define_singleton_method(rb_cCeguiOgreRenderer,"bootstrap",RUBY_METHOD_FUNC(_ogre_bootstrap),0);
#endif

#if HAVE_CEGUI_RENDERERMODULES_IRRLICHT_RENDERER_H
	rb_cCeguiIrrlichtRenderer = rb_define_class_under(rb_mCegui,"IrrlichtRenderer",rb_cCeguiRenderer);
	rb_define_singleton_method(rb_cCeguiIrrlichtRenderer,"new",RUBY_METHOD_FUNC(_irrlicht_alloc),1);
	rb_define_singleton_method(rb_cCeguiIrrlichtRenderer,"bootstrap",RUBY_METHOD_FUNC(_irrlicht_bootstrap),1);
#endif
}
