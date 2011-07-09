#include "ceguiexception.hpp"
#define _self wrap<CEGUI::Exception*>(self)

VALUE rb_mCeguiException;
VALUE rb_eCeguiUnknownObjectException,rb_eCeguiAlreadyExistsException,rb_eCeguiInvalidRequestException;
/*
*/
VALUE CeguiException_getMessage(VALUE self)
{
	return wrap(_self->getMessage());
}
/*
*/
VALUE CeguiException_getFile(VALUE self)
{
	return wrap(_self->getFileName());
}
/*
*/
VALUE CeguiException_getLine(VALUE self)
{
	return UINT2NUM(_self->getLine());
}
/*
*/
void Init_CeguiException(VALUE rb_mCegui)
{
	#if 0
	rb_mCegui = rb_define_module("CEGUI");
	#endif
	rb_mCeguiException = rb_define_module_under(rb_mCegui,"Exception");
	
	rb_define_method(rb_mCeguiException,"to_s",RUBY_METHOD_FUNC(CeguiException_getMessage),0);

	rb_define_method(rb_mCeguiException,"file",RUBY_METHOD_FUNC(CeguiException_getFile),0);
	rb_define_method(rb_mCeguiException,"line",RUBY_METHOD_FUNC(CeguiException_getLine),0);
	rb_define_alias(rb_mCeguiException,"to_i","line");
	
	rb_eCeguiUnknownObjectException = rb_define_class_under(rb_mCeguiException,"UnknownObject",rb_eException);
	rb_include_module(rb_eCeguiUnknownObjectException,rb_mCeguiException);
	
	rb_eCeguiInvalidRequestException = rb_define_class_under(rb_mCeguiException,"InvalidRequest",rb_eException);
	rb_include_module(rb_eCeguiInvalidRequestException,rb_mCeguiException);

	rb_eCeguiAlreadyExistsException = rb_define_class_under(rb_mCeguiException,"AlreadyExists",rb_eException);
	rb_include_module(rb_eCeguiAlreadyExistsException,rb_mCeguiException);


}
