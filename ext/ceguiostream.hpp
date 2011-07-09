#ifndef __RubyCeguiOstream_H__
#define __RubyCeguiOstream_H__

#include "main.hpp"
#include <iostream>
#include <sstream>

class RubyOstream : public std::ostringstream{
public:
	RubyOstream(VALUE val);
	bool operator!() const;
	bool good() const;
	RubyOstream& put(char s);
	RubyOstream& write(const char *s,size_t size);
	
	streampos tellp();	
	RubyOstream& seekp ( streampos pos );
	RubyOstream& seekp ( streamoff off, ios_base::seekdir dir );
	
	RubyOstream& flush();
private:
	VALUE value;
};

#endif /* __RubyCeguiOstream_H__ */
