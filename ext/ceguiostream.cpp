#include "ceguiostream.hpp"
RubyStreamBuf::RubyStreamBuf(VALUE val) : std::streambuf(),value(val)
{
};

int RubyStreamBuf::overflow(int c)
{
	rb_funcall(value,rb_intern("<<"),1,rb_str_new2((char*)&c));
//	std::cout << (char*)&c;
	return 0;
}

size_t RubyStreamBuf::xsputn( const char * s, size_t n )
{
	std::cout << "xsputn" << std::endl;
	return n;
}

//*
RubyStream::RubyStream(VALUE val)
{
	this->buf = new RubyStreamBuf(val);
	std::ostream(this->buf);
}

RubyStream::~RubyStream()
{
//	delete buf;
}
//*/
