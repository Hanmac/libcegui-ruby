#include "ceguifont.hpp"
#include "ceguieventset.hpp"
#include "ceguipropertyset.hpp"
#include "ceguixmlserializer.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::Font*>(self)
#define _manager CEGUI::FontManager::getSingletonPtr()

VALUE rb_cCeguiFont;

namespace CeguiFont {

macro_attr(NativeResolution,CEGUI::Sizef)
macro_attr_bool(AutoScaled)

singlereturn(getName)


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
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	array[2]=_getName(self);
	return rb_f_sprintf(3,array);
}

/*
(VALUE self,VALUE buffer,VALUE text,VALUE position,VALUE clip_rect,VALUE colors,VALUE space_extra,VALUE x_scale,VALUE y_scale)
*/
VALUE _drawText(int argc,VALUE *argv,VALUE self)
{
	float cspace_extra=0.0f,cx_scale=1.0f,cy_scale=1.0f;
	VALUE buffer,text,position,clip_rect,colours,space_extra,x_scale,y_scale;
	rb_scan_args(argc, argv, "53",&buffer,&text,&position,&clip_rect,&colours,&space_extra,&x_scale,&y_scale);
	if(!NIL_P(space_extra))
		cspace_extra = NUM2DBL(space_extra);
	if(!NIL_P(x_scale))
		x_scale = NUM2DBL(x_scale);
	if(!NIL_P(y_scale))
		y_scale = NUM2DBL(y_scale);
	_self->drawText(*wrap<CEGUI::GeometryBuffer*>(buffer),wrap<CEGUI::String>(text),wrap<CEGUI::Vector2f>(position),
	wrap<CEGUI::Rectf*>(clip_rect),wrap<CEGUI::ColourRect>(colours), cspace_extra,cx_scale, cy_scale);
	return self;
}

/*
*/
VALUE _writeXML(VALUE self,VALUE xml)
{
	CEGUI::XMLSerializer *temp =wrap<CEGUI::XMLSerializer*>(xml);
	_self->writeXMLToStream(*temp);
	return self;
}

/*
*/
VALUE _Manager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_manager->getIterator());
	return self;
}


/*
*/
VALUE _Manager_isDefined(VALUE self,VALUE name)
{
	return wrap(_manager->isDefined(wrap<CEGUI::String>(name)));
}
/*
*/
VALUE _Manager_get(VALUE self,VALUE name)
{
	CEGUI::String cname = wrap<CEGUI::String>(name);
	return _manager->isDefined(cname) ? wrap(&_manager->get(cname)) : Qnil;
}

/*
*/
VALUE _Manager_create(int argc,VALUE *argv,VALUE self)
{
	VALUE path,resource_group;
	rb_scan_args(argc, argv, "11",&path,&resource_group);
	try{
		VALUE result = wrap(&_manager->createFromFile(wrap<CEGUI::String>(path),
			wrap<CEGUI::String>(resource_group)));
		rb_funcall2(result,rb_intern("initialize"),argc,argv);
		return result;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}


/*
*/
VALUE _Manager_createAll(int argc,VALUE *argv,VALUE self)
{
	VALUE pattern,resource_group;
	rb_scan_args(argc, argv, "11",&pattern,&resource_group);
	_manager->createAll(wrap<CEGUI::String>(pattern),wrap<CEGUI::String>(resource_group));
	return self;
}

/*
*/
VALUE _Manager_createFreeTypeFont(int argc,VALUE *argv,VALUE self)
{
	VALUE font_name, point_size, anti_aliased, font_filename, resource_group, auto_scaled, native_horz_res, native_vert_res;
	rb_scan_args(argc, argv, "44",&font_name, &point_size, &anti_aliased, &font_filename, &resource_group, &auto_scaled, &native_horz_res, &native_vert_res);
	float cnative_horz_res=640.0f,cnative_vert_res=480.0f;
	if(!NIL_P(native_horz_res))
		cnative_horz_res = NUM2DBL(native_horz_res);
	if(!NIL_P(native_vert_res))
		cnative_vert_res = NUM2DBL(native_vert_res);
	CEGUI::String cfont_name = wrap<CEGUI::String>(font_name);
	CEGUI::String cfont_filename = wrap<CEGUI::String>(font_filename);
	CEGUI::String cresource_group = wrap<CEGUI::String>(resource_group);
	try{
		VALUE result = wrap(&_manager->createFreeTypeFont(cfont_name, NUM2DBL(point_size),
			RTEST(anti_aliased),cfont_filename,cresource_group,
			RTEST(auto_scaled), cnative_horz_res, cnative_vert_res));
		rb_funcall2(result,rb_intern("initialize"),argc,argv);
		return result;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _Manager_createPixmapFont(int argc,VALUE *argv,VALUE self)
{
	VALUE font_name, imageset_filename, resource_group, auto_scaled, native_horz_res, native_vert_res;
	rb_scan_args(argc, argv, "24",&font_name, &imageset_filename, &resource_group, &auto_scaled, &native_horz_res, &native_vert_res);
	float cnative_horz_res=640.0f,cnative_vert_res=480.0f;
	if(!NIL_P(native_horz_res))
		cnative_horz_res = NUM2DBL(native_horz_res);
	if(!NIL_P(native_vert_res))
		cnative_vert_res = NUM2DBL(native_vert_res);
	CEGUI::String cfont_name = wrap<CEGUI::String>(font_name);
	CEGUI::String cimageset_filename = wrap<CEGUI::String>(imageset_filename);
	CEGUI::String cresource_group = wrap<CEGUI::String>(resource_group);
	try{
		VALUE result = wrap(&_manager->createPixmapFont(cfont_name, cimageset_filename,
			cresource_group, RTEST(auto_scaled),cnative_horz_res, cnative_vert_res));
		rb_funcall2(result,rb_intern("initialize"),argc,argv);
		return result;
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
/*
*/
VALUE _Manager_getDefaultResourceGroup(VALUE self)
{
	return wrap(CEGUI::Font::getDefaultResourceGroup());
}
/*
*/
VALUE _Manager_setDefaultResourceGroup(VALUE self,VALUE val)
{
	CEGUI::Font::setDefaultResourceGroup(wrap<CEGUI::String>(val));
	return val;
}

}

void Init_CeguiFont(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
	
	rb_define_attr(rb_cCeguiFont,"nativeResolution",1,1);
	rb_define_attr(rb_cCeguiFont,"autoScaled",1,1);
#endif
	using namespace CeguiFont;

	rb_cCeguiFont = rb_define_class_under(rb_mCegui,"Font",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiFont);

	rb_extend_object(rb_cCeguiFont,rb_mCeguiEventSet);
	rb_include_module(rb_cCeguiFont,rb_mCeguiPropertySet);

	rb_define_attr_method(rb_cCeguiFont,"nativeResolution",_getNativeResolution,_setNativeResolution);
	rb_define_attr_method(rb_cCeguiFont,"autoScaled",_getAutoScaled,_setAutoScaled);



	rb_define_method(rb_cCeguiFont,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cCeguiFont,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cCeguiFont,"draw",RUBY_METHOD_FUNC(_drawText),-1);

	rb_define_method(rb_cCeguiFont,"writeXML",RUBY_METHOD_FUNC(_writeXML),1);


	rb_define_singleton_method(rb_cCeguiFont,"[]",RUBY_METHOD_FUNC(_Manager_get),1);
	rb_define_singleton_method(rb_cCeguiFont,"each",RUBY_METHOD_FUNC(_Manager_each),0);

	rb_define_singleton_method(rb_cCeguiFont,"defined?",RUBY_METHOD_FUNC(_Manager_isDefined),1);

	rb_define_singleton_method(rb_cCeguiFont,"new",RUBY_METHOD_FUNC(_Manager_create),-1);
	
	rb_define_singleton_method(rb_cCeguiFont,"createFreeTypeFont",RUBY_METHOD_FUNC(_Manager_createFreeTypeFont),-1);
	rb_define_singleton_method(rb_cCeguiFont,"createPixmapFont",RUBY_METHOD_FUNC(_Manager_createPixmapFont),-1);
	
	rb_define_singleton_method(rb_cCeguiFont,"createAll",RUBY_METHOD_FUNC(_Manager_createAll),-1);

	rb_define_singleton_method(rb_cCeguiFont,"defaultResourceGroup",RUBY_METHOD_FUNC(_Manager_getDefaultResourceGroup),0);
	rb_define_singleton_method(rb_cCeguiFont,"defaultResourceGroup=",RUBY_METHOD_FUNC(_Manager_setDefaultResourceGroup),1);

}
