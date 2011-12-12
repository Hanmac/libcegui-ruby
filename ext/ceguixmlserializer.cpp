#include "ceguixmlserializer.hpp"
#define _self wrap<CEGUI::XMLSerializer*>(self)
VALUE rb_cCeguiXMLSerializer;

/*
*/
VALUE CeguiXMLSerializer_create(VALUE self,VALUE io)
{
//	std::ostream *os = new RubyStream(io);
	std::ostream *os = new std::ostream(new RubyStreamBuf(io));
	return wrap(new CEGUI::XMLSerializer(*os));
}
/*
*/
VALUE CeguiXMLSerializer_openTag(VALUE self,VALUE name)
{
	_self->openTag(wrap<CEGUI::String>(name));
	if(rb_block_given_p()){
		VALUE val = rb_block_proc();
//		rb_proc_call(rb_block_proc(),self);
		rb_obj_instance_eval(0,&val,self);
//		rb_funcall(self,rb_intern("instance_eval"),1,rb_block_proc());
//		rb_funcall(self,rb_intern("instance_eval"),0);
		_self->closeTag();
	}
	return self;
}
/*
*/
VALUE CeguiXMLSerializer_attribute(VALUE self,VALUE key,VALUE value)
{
	key = rb_funcall(key,rb_intern("to_s"),0);
	value = rb_funcall(value,rb_intern("to_s"),0);
	CEGUI::String ckey=wrap<CEGUI::String>(key);
	if(ckey.find('=')!=std::string::npos)
		ckey.erase(ckey.size()-1);
	_self->attribute(ckey,wrap<CEGUI::String>(value));
	return self;
}
/*
*/
VALUE CeguiXMLSerializer_text(VALUE self,VALUE text)
{
	_self->text(wrap<CEGUI::String>(text));
	return self;
}

/*
*/
VALUE CeguiXMLSerializer_closeTag(VALUE self)
{
	_self->closeTag();
	return self;
}

/*
*/
VALUE CeguiXMLSerializer_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE methID,arg;
	rb_scan_args(argc, argv, "1*",&methID,&arg);
	methID = rb_funcall(methID,rb_intern("to_s"),0);
	
	if((argc==1) and rb_block_given_p())
		CeguiXMLSerializer_openTag(self,methID);
	else if((wrap<CEGUI::String>(methID).find('=')!=std::string::npos) and (argc==2)){
		rb_scan_args(argc, argv, "20",&methID,&arg);
		CeguiXMLSerializer_attribute(self,methID,arg);
	}else
		return rb_call_super(argc,argv);
	
	return self;
}

/*
 * Document-class: CEGUI::XMLSerializer
 * 
 * This class represents an XMLSerializer.
*/ 
void Init_CeguiXMLSerializer(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif
	rb_cCeguiXMLSerializer = rb_define_class_under(rb_mCegui,"XMLSerializer",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiXMLSerializer);
	
	rb_define_singleton_method(rb_cCeguiXMLSerializer,"new",RUBY_METHOD_FUNC(CeguiXMLSerializer_create),1);
//	rb_define_method(rb_cCeguiXMLSerializer,"initialize",RUBY_METHOD_FUNC(CeguiXMLSerializer_initialize),4);
//	rb_define_private_method(rb_cCeguiXMLSerializer,"initialize_copy",RUBY_METHOD_FUNC(CeguiXMLSerializer_initialize_copy),1);
	
	rb_define_method(rb_cCeguiXMLSerializer,"openTag",RUBY_METHOD_FUNC(CeguiXMLSerializer_openTag),1);
	rb_define_method(rb_cCeguiXMLSerializer,"attribute",RUBY_METHOD_FUNC(CeguiXMLSerializer_attribute),2);
	rb_define_method(rb_cCeguiXMLSerializer,"text",RUBY_METHOD_FUNC(CeguiXMLSerializer_text),1);
	rb_define_method(rb_cCeguiXMLSerializer,"closeTag",RUBY_METHOD_FUNC(CeguiXMLSerializer_closeTag),0);
	
	rb_define_method(rb_cCeguiXMLSerializer,"method_missing",RUBY_METHOD_FUNC(CeguiXMLSerializer_method_missing),-1);
}
