#ifndef __RubyCEGUIMain_H__
#define __RubyCEGUIMain_H__

#include <ruby.h>
#include <CEGUI.h>

#include RUBY_EXTCONF_H

#include <typeinfo>
#include <algorithm>
template <typename T>
VALUE wrap(T *arg){
	rb_warn("unknown convertion from %s to VALUE. return nil instat.",typeid(T).name());
	return Qnil;
};

template <typename T>
T wrap(const VALUE &arg){
	rb_warn("unknown convertion from VALUE to %s. return %s() instat.",typeid(T).name(),typeid(T).name());
	return T();
};

template <typename T>
VALUE wrap(const T &arg){
	return wrap(new T(arg));
};

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

/*
template <typename T>
T wrap(const VALUE &val,typename T default_value )
{
	if(val == Qnil)
		return default_value;
	else
		return wrap<typename T>(val);
}
//*/
//template <typename T>
//void wrap_each1(T begin,T end)
//{
//	for(T cit = begin; cit != end; ++cit)
//		rb_yield(wrap(*cit));
//}
//template <typename T>
//void wrap_each2(T begin,T end)
//{
//	for(T cit = begin; cit != end; ++cit)
//			rb_yield_values(2,wrap(cit->first),wrap(cit->second));
//}

//template <typename T>
//void wrap_each2a(T begin,T end)
//{
//	for(T cit = begin; cit != end; ++cit)
//			rb_yield(wrap(cit->first));
//}

template <typename T>
void wrap_each(CEGUI::ConstBaseIterator<std::map<CEGUI::String, T, CEGUI::String::FastLessCompare> > it)
{
	for(it.toStart(); !it.isAtEnd(); ++it)
			rb_yield_values(2,wrap(it.getCurrentKey()),wrap(it.getCurrentValue()));
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

bool cegui_subscriberfunc(const CEGUI::EventArgs& arg, void * obj);

#define macro_attr(klass,attr,type) \
VALUE Cegui##klass##_get##attr(VALUE self)\
{return wrap(_self->get##attr());}\
\
VALUE Cegui##klass##_set##attr(VALUE self,VALUE other)\
{\
	_self->set##attr(wrap<type>(other));\
	return other;\
}

#define macro_attr_with_func(klass,attr,getfunc,setfunc) \
VALUE Cegui##klass##_get##attr(VALUE self)\
{return getfunc(_self->get##attr() );}\
\
VALUE Cegui##klass##_set##attr(VALUE self,VALUE other)\
{\
	_self->set##attr( setfunc(other) );\
	return other;\
}

//*/
#define macro_attr_prop(klass,attr,type) \
VALUE Cegui##klass##_get_##attr(VALUE self)\
{return wrap(_self->attr);}\
\
VALUE Cegui##klass##_set_##attr(VALUE self,VALUE other)\
{\
	_self->attr = wrap<type>(other);\
	return other;\
}

#define macro_attr_prop_with_func(klass,attr,getfunc,setfunc) \
VALUE Cegui##klass##_get_##attr(VALUE self)\
{return getfunc(_self->attr);}\
\
VALUE Cegui##klass##_set_##attr(VALUE self,VALUE other)\
{\
	_self->attr = setfunc(other);\
	return other;\
}

#define RBOOL(val) (val) ? Qtrue : Qfalse

#endif /* __RubyCeguiMain_H__ */

