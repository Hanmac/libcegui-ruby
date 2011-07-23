#ifndef __RubyCeguiOstream_H__
#define __RubyCeguiOstream_H__

#include "main.hpp"
#include <iostream>
#include <ostream>
//#include <sstream>

class RubyStreamBuf : public std::streambuf{
public:
	RubyStreamBuf(VALUE val);
	int overflow(int c);
	size_t xsputn ( const char * s, size_t n );
private:
	VALUE value;
};


class RubyStream : public std::ostream{
public:
	RubyStream(VALUE val);
	~RubyStream();
private:
	RubyStreamBuf *buf;	
};
#endif /* __RubyCeguiOstream_H__ */
