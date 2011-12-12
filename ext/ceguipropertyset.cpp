#include "ceguipropertyset.hpp"
#include "ceguiproperty.hpp"
#include "ceguiexception.hpp"

#include "ceguicolorrect.hpp"
#include "ceguiquaternion.hpp"
#include "ceguivector2.hpp"

#include "ceguifont.hpp"
#include "ceguiimage.hpp"

#include "ceguiubox.hpp"
#include "ceguiusize.hpp"
#include "ceguiurect.hpp"
#include "ceguiuvector2.hpp"

#include "ceguifalagardenums.hpp"

#define _self wrap<CEGUI::PropertySet*>(self)
VALUE rb_mCeguiPropertySet;

std::map<VALUE,CEGUI::PropertySet*> propertysetholder;
/*
*/
VALUE CeguiPropertySet_addProperty(VALUE self,VALUE prop)
{
	try{
		_self->addProperty(wrap<CEGUI::Property*>(prop));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}
/*
*/
VALUE CeguiPropertySet_isPropertyPresent(VALUE self,VALUE name)
{
	return wrap(_self->isPropertyPresent(wrap<CEGUI::String>(name)));
}


/*
*/
VALUE _getProperty_impl(CEGUI::PropertySet* self,const CEGUI::String &cname)
{
	const CEGUI::String &type = self->getPropertyInstance(cname)->getDataType();
	if(type == "bool" )
		return wrap(self->getProperty<bool>(cname));
	else if(type == "float" )
		return wrap(self->getProperty<float>(cname));
	else if(type == "uint" )
		return wrap(self->getProperty<uint>(cname));
	else if(type == "ColourRect" )
		return wrap(self->getProperty<CEGUI::ColourRect>(cname));
	else if(type == "UBox" )
		return wrap(self->getProperty<CEGUI::UBox>(cname));
	else if(type == "URect" )
		return wrap(self->getProperty<CEGUI::URect>(cname));
	else if(type == "USize" )
		return wrap(self->getProperty<CEGUI::USize>(cname));
	else if(type == "UVector2" )
		return wrap(self->getProperty<CEGUI::UVector2>(cname));
	else if(type == "Quaternion" )
		return wrap(self->getProperty<CEGUI::Quaternion>(cname));
	else if(type == "Font*" )
		return wrap(self->getProperty<CEGUI::Font*>(cname));
	else if(type == "Image*" )
		return wrap(self->getProperty<CEGUI::Image*>(cname));
	else if(type == "HorizontalTextFormatting" )
		return wrap(self->getProperty<CEGUI::HorizontalTextFormatting>(cname));
	else
		return wrap(self->getProperty(cname));
}
/*
*/
VALUE CeguiPropertySet_getProperty(VALUE self,VALUE name)
{
	try{
		return _getProperty_impl(_self,wrap<CEGUI::String>(name));
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return Qnil;
}
void _setProperty_impl(CEGUI::PropertySet* self,const CEGUI::String &name, VALUE val)
{
	if(rb_obj_is_kind_of(val, rb_cString)){
		self->setProperty(name,wrap<CEGUI::String>(val));
	}else {
		const CEGUI::String &type = self->getPropertyInstance(name)->getDataType();
		if(type == "bool" )
			self->setProperty<bool>(name,wrap<bool>(val));
		else if(type == "float" )
			self->setProperty<float>(name,wrap<float>(val));
		else if(type == "uint" )
			self->setProperty<uint>(name,NUM2UINT(val));
		else if(type == "ColourRect" ){
			self->setProperty<CEGUI::ColourRect>(name,wrap<CEGUI::ColourRect>(val));
		}else if(type == "UBox" )
			self->setProperty<CEGUI::UBox>(name,wrap<CEGUI::UBox>(val));
		else if(type == "URect" )
			self->setProperty<CEGUI::URect>(name,wrap<CEGUI::URect>(val));
		else if(type == "USize" )
			self->setProperty<CEGUI::USize>(name,wrap<CEGUI::USize>(val));
		else if(type == "UVector2" )
			self->setProperty<CEGUI::UVector2>(name,wrap<CEGUI::UVector2>(val));
		else if(type == "Quaternion" )
			self->setProperty<CEGUI::Quaternion>(name,wrap<CEGUI::Quaternion>(val));
		else if(type == "Font*" )
			self->setProperty<CEGUI::Font*>(name,wrap<CEGUI::Font*>(val));
		else if(type == "Image*" )
			self->setProperty<CEGUI::Image*>(name,wrap<CEGUI::Image*>(val));
		else
			self->setProperty(name,wrap<CEGUI::String>(val));
	}
}

/*
*/
VALUE CeguiPropertySet_setProperty(VALUE self,VALUE name,VALUE val)
{
	try{
		_setProperty_impl(_self,wrap<CEGUI::String>(name),val);
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}
	return self;
}

//CEGUI::HorizontalAlignment
//CEGUI::VerticalAlignment

/*
*/
VALUE CeguiPropertySet_each_property(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap_each(_self->getPropertyIterator());
	return self;
}

/*
*/
VALUE CeguiPropertySet_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE methID,arg,val;
	rb_scan_args(argc, argv, "1*",&methID,&arg);
	CEGUI::String propname;
	std::string cname = rb_id2name(SYM2ID(methID));
	bool setter=false;
	if(cname.find('=')!=std::string::npos){
		setter=true;
		cname.erase(cname.size()-1);
	}
	try{
		if(_self->isPropertyPresent(cname)){
			if(setter){
				rb_scan_args(argc, argv, "11",&methID,&val);//check argc
				_setProperty_impl(_self,cname,val);
				return self;
			}else{
				rb_scan_args(argc, argv, "10",&methID);//check argc
				return _getProperty_impl(_self,cname);
			}
		}else{
			CEGUI::PropertySet::PropertyIterator it = _self->getPropertyIterator();
			for(it.toStart(); !it.isAtEnd(); ++it){
				propname = it.getCurrentKey();
				std::transform(cname.begin(), cname.end(), cname.begin(),std::ptr_fun<int,int>(std::tolower));
				std::transform(propname.begin(), propname.end(), propname.begin(),std::ptr_fun<int,int>(std::tolower));
				if(propname.compare(cname)==0){
					if(setter){
						rb_scan_args(argc, argv, "11",&methID,&val);//check argc
						_setProperty_impl(_self,it.getCurrentKey(),val);
						return self;
					}else{
						rb_scan_args(argc, argv, "10",&methID);//check argc
						return _getProperty_impl(_self,it.getCurrentKey());
					}
				}
			}
		}
	}catch(CEGUI::Exception& e){
		rb_raise(e);
	}

	return rb_call_super(argc,argv);
}
void Init_CeguiPropertySet(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");
#endif
	rb_mCeguiPropertySet = rb_define_module_under(rb_mCegui,"PropertySet");

	rb_define_method(rb_mCeguiPropertySet,"each_property",RUBY_METHOD_FUNC(CeguiPropertySet_each_property),0);
	
	rb_define_method(rb_mCeguiPropertySet,"method_missing",RUBY_METHOD_FUNC(CeguiPropertySet_method_missing),-1);

	rb_define_method(rb_mCeguiPropertySet,"addProperty",RUBY_METHOD_FUNC(CeguiPropertySet_addProperty),1);
	rb_define_method(rb_mCeguiPropertySet,"hasProperty?",RUBY_METHOD_FUNC(CeguiPropertySet_isPropertyPresent),1);

	rb_define_method(rb_mCeguiPropertySet,"getProperty",RUBY_METHOD_FUNC(CeguiPropertySet_getProperty),1);
	rb_define_method(rb_mCeguiPropertySet,"setProperty",RUBY_METHOD_FUNC(CeguiPropertySet_setProperty),2);
}
