#include "ceguiostream.hpp"
RubyOstream::RubyOstream(VALUE val) : std::ostringstream(),value(val){};

bool RubyOstream::operator!()const{
	return false;
};
bool RubyOstream::good()const{
	std::cout << "good called" << std::endl;
	return true;
};

RubyOstream& RubyOstream::put(char s){
	rb_funcall(value,rb_intern("<<"),1,rb_str_new2(&s));
	return *this;
};
RubyOstream& RubyOstream::write(const char *s,size_t size){
	rb_funcall(value,rb_intern("write"),1,rb_str_new2(s));
	return *this;
};

RubyOstream::streampos RubyOstream::tellp(){
	return NUM2INT(rb_funcall(value,rb_intern("tell"),0));
};

RubyOstream& RubyOstream::seekp( RubyOstream::streampos pos ){
	rb_funcall(value,rb_intern("seek"),1,NUM2INT(pos));
	return *this;
};
RubyOstream& RubyOstream::seekp(RubyOstream::streamoff off, ios_base::seekdir dir ){
	rb_funcall(value,rb_intern("seek"),1,INT2NUM(off),INT2NUM(dir));
	return *this;
};

RubyOstream& RubyOstream::flush(){
	rb_funcall(value,rb_intern("flush"),0);
	return *this;
};
