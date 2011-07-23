#include "ceguipropertyset.hpp"
#include "ceguiproperty.hpp"
#define _self wrap<CEGUI::PropertySet*>(self)
VALUE rb_mCeguiPropertySet;
/*
*/
VALUE CeguiPropertySet_getProperty(VALUE self,VALUE name)
{
	return wrap(_self->getProperty(wrap<CEGUI::String>(name)));
}
/*
*/
VALUE CeguiPropertySet_setProperty(VALUE self,VALUE name,VALUE val)
{
	_self->setProperty(wrap<CEGUI::String>(name),wrap<CEGUI::String>(val));
	return self;
}
/*
*/
VALUE CeguiPropertySet_each_property(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getIterator());
	return self;
}

/*
*/
VALUE CeguiPropertySet_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE methID,arg,val;
	rb_scan_args(argc, argv, "1*",&methID,&arg);
	methID = rb_funcall(methID,rb_intern("to_s"),0);
	CEGUI::String propname;
	std::string cname = StringValueCStr(methID);
	bool setter=false;
	if(cname.find('=')!=std::string::npos){
		setter=true;
		cname.erase(cname.size()-1);
	}
	if(_self->isPropertyPresent(cname)){
		if(setter){
			rb_scan_args(argc, argv, "11",&methID,&val);//check argc
			_self->setProperty(cname,StringValueCStr(val));
			return self;
		}else{
			rb_scan_args(argc, argv, "10",&methID);//check argc
			return wrap(_self->getProperty(cname));
		}
	}else{
		CEGUI::PropertySet::Iterator it = _self->getIterator();
		for(it.toStart(); !it.isAtEnd(); ++it){
			propname = it.getCurrentKey();
			std::transform(cname.begin(), cname.end(), cname.begin(),std::ptr_fun<int,int>(std::tolower));
			std::transform(propname.begin(), propname.end(), propname.begin(),std::ptr_fun<int,int>(std::tolower));
			if(propname.compare(cname)==0){
				if(setter){
					rb_scan_args(argc, argv, "11",&methID,&val);//check argc
					_self->setProperty(it.getCurrentKey(),StringValueCStr(val));
					return self;
				}else{
					rb_scan_args(argc, argv, "10",&methID);//check argc
					return wrap(_self->getProperty(it.getCurrentKey()));
				}
			}
		}
	}
	return rb_call_super(argc,argv);
}
void Init_CeguiPropertySet(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
#endif
	rb_mCeguiPropertySet = rb_define_module_under(rb_mCegui,"PropertySet");

	rb_define_method(rb_mCeguiPropertySet,"each_property",RUBY_METHOD_FUNC(CeguiPropertySet_each_property),0);
	
	rb_define_method(rb_mCeguiPropertySet,"method_missing",RUBY_METHOD_FUNC(CeguiPropertySet_method_missing),-1);

	rb_define_method(rb_mCeguiPropertySet,"getProperty",RUBY_METHOD_FUNC(CeguiPropertySet_getProperty),1);
	rb_define_method(rb_mCeguiPropertySet,"setProperty",RUBY_METHOD_FUNC(CeguiPropertySet_setProperty),2);
}
