#ifndef __RubyCEGUIMain_H__
#define __RubyCEGUIMain_H__

#include <ruby.h>
#include <CEGUI/CEGUI.h>

#include RUBY_EXTCONF_H

#include <algorithm>

template <typename T>
VALUE wrap(T *arg);

template <typename T>
T wrap(const VALUE &arg);


template <typename T>
VALUE wrap(const T &arg){
	return wrap(new T(arg));
};

template <typename T>
bool is_wrapable(const VALUE &arg);


template <typename T>
VALUE wrap(const std::vector<T> &vec){
	VALUE result = rb_ary_new();
	typename std::vector<T>::const_iterator it;
	for ( it=vec.begin() ; it != vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
};


template <>
inline VALUE wrap< CEGUI::String >(const CEGUI::String &st )
{
	return rb_str_new2(st.c_str());
}

template <>
inline CEGUI::String wrap< CEGUI::String >(const VALUE &val )
{
	if(NIL_P(val))
		return "";
	else if (rb_obj_is_kind_of(val, rb_cString))
		return rb_string_value_cstr((volatile VALUE*)(&val));
	else
		return wrap< CEGUI::String >(rb_funcall(val,rb_intern("to_s"),0));
}


template <>
inline float wrap< float >(const VALUE &val )
{
	return NUM2DBL(val);
}

template <>
inline VALUE wrap< float >(const float &st )
{
	return DBL2NUM(st);
}

template <>
inline uint wrap< uint >(const VALUE &val )
{
	return NUM2UINT(val);
}

template <>
inline VALUE wrap< uint >(const uint &st )
{
	return UINT2NUM(st);
}

template <>
inline bool wrap< bool >(const VALUE &val )
{
	return RTEST(val);
}

template <>
inline VALUE wrap< bool >(const bool &st )
{
	return st ? Qtrue : Qfalse;
}

template <>
inline VALUE wrap< CEGUI::XMLAttributes >(const CEGUI::XMLAttributes &st )
{
	VALUE hash = rb_hash_new();
	for( unsigned int i=0 ; i < st.getCount(); ++i)
		rb_hash_aset(hash,wrap(st.getName(i)),wrap(st.getValue(i)));
	return hash;
}

template <typename T>
VALUE wrap(const std::pair<T,T> &pair){
	return rb_range_new(wrap<T>(pair.first),wrap<T>(pair.second),0);
};

template <typename T>
std::pair<T,T> wrap_pair(const VALUE &val){
	VALUE b= rb_funcall(val,rb_intern("begin"),0);
	VALUE e= rb_funcall(val,rb_intern("end"),0);
	return std::make_pair(wrap<T>(b),wrap<T>(e));
}


typedef std::pair<float, float> Range;

template <>
inline Range wrap< Range >(const VALUE &val )
{
	return wrap_pair<float>(val);
}

template <typename T>
void wrap_each(CEGUI::ConstMapIterator<std::map<CEGUI::String, T, CEGUI::StringFastLessCompare > > it)
{
	for(it.toStart(); !it.isAtEnd(); ++it)
			rb_yield_values(2,wrap(it.getCurrentKey()),wrap(it.getCurrentValue()));
}


template <typename T>
void wrap_each(CEGUI::ConstVectorIterator<std::vector<T> > it)
{
	for(it.toStart(); !it.isAtEnd(); ++it)
		rb_yield_values(1,wrap(it.getCurrentValue()));
}
template <typename T>
void wrap_each(CEGUI::ConstVectorIterator<std::multiset<T> > it)
{
	for(it.toStart(); !it.isAtEnd(); ++it)
		rb_yield_values(1,wrap(it.getCurrentValue()));
}

/*
*/
VALUE Cegui_dummy0(VALUE self);
VALUE Cegui_dummy1(VALUE self,VALUE obj1);
VALUE Cegui_dummy2(VALUE self,VALUE obj1,VALUE obj2);
VALUE Cegui_dummy3(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3);
VALUE Cegui_dummy4(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3,VALUE obj4);

inline void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE))
{
	rb_define_method(klass,name.c_str(),RUBY_METHOD_FUNC(get),0);
	rb_define_method(klass,(name + "=").c_str(),RUBY_METHOD_FUNC(set),1);
}
//#define rb_define_attr(klass,attr,n,m) rb_define_attr_method(klass,attr,Cegui##klass##_get##attr,Cegui##klass##_set##attr)

inline void rb_define_single_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE))
{
	rb_define_singleton_method(klass,name.c_str(),RUBY_METHOD_FUNC(get),0);
	rb_define_singleton_method(klass,(name + "=").c_str(),RUBY_METHOD_FUNC(set),1);
}

bool cegui_subscriberfunc(const CEGUI::EventArgs& arg, void * obj);


template <typename T>
T* unwrapPtr(const VALUE &obj,const VALUE &klass)
{
	if (rb_obj_is_kind_of(obj, klass)){
		T *temp;
		Data_Get_Struct( obj, T, temp);
		return temp;
	}else{
		rb_raise(rb_eTypeError,
				"Expected %s got %s!",
				rb_class2name(klass),
				rb_obj_classname(obj)
		);
		return NULL;
	}

}

template <typename T>
T* unwrapWindow(const VALUE &obj,const VALUE &klass)
{
	if (rb_obj_is_kind_of(obj, klass)){
		return (T*)(wrap< CEGUI::Window* >(obj));
	}else{
		rb_raise(rb_eTypeError,
				"Expected %s got %s!",
				rb_class2name(klass),
				rb_obj_classname(obj)
		);
		return NULL;
	}
}



VALUE rb_funcall(VALUE obj,const char *name);

template<typename T>
VALUE rb_funcall(VALUE obj,const char *name,T param)
{
	return rb_funcall(obj,rb_intern(name),1,wrap(param));
}
inline void rb_raise(VALUE exception){
	rb_funcall(rb_mKernel,rb_intern("raise"),1,exception);
}

#define macro_attr(attr,type) \
VALUE _get##attr(VALUE self)\
{return wrap(_self->get##attr());}\
\
VALUE _set##attr(VALUE self,VALUE other)\
{\
	try{\
		_self->set##attr(wrap<type>(other));\
	}catch(CEGUI::Exception& e){\
		rb_raise(e);\
		return Qnil;\
	}\
	return other;\
}

#define macro_attr_bool(attr) \
VALUE _get##attr(VALUE self)\
{return wrap(_self->is##attr());}\
\
VALUE _set##attr(VALUE self,VALUE other)\
{\
	try{\
		_self->set##attr(wrap<bool>(other));\
	}catch(CEGUI::Exception& e){\
		rb_raise(e);\
		return Qnil;\
	}\
	return other;\
}

//*/
#define macro_attr_prop(attr,type) \
VALUE _get_##attr(VALUE self)\
{return wrap(_self->attr);}\
\
VALUE _set_##attr(VALUE self,VALUE other)\
{\
	_self->attr = wrap<type>(other);\
	return other;\
}

#define singlefunc(func) \
VALUE _##func(VALUE self)\
{\
	try{\
		_self->func();\
	}catch(CEGUI::Exception& e){\
		rb_raise(e);\
	}\
	return self;\
}
#define singlereturn(func) \
VALUE _##func(VALUE self)\
{\
	try{\
		return wrap(_self->func());\
	}catch(CEGUI::Exception& e){\
		rb_raise(e);\
	}\
	return Qnil;\
}


#endif /* __RubyCeguiMain_H__ */

