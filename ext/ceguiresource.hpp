/*
 * ceguiresource.hpp
 *
 *  Created on: 29.12.2011
 *      Author: hanmac
 */

#ifndef CEGUIRESOURCE_HPP_
#define CEGUIRESOURCE_HPP_

#include "ceguiexception.hpp"

class RubyResource{
public:
	RubyResource(CEGUI::String n) : name(n) {};
	CEGUI::String name;
};

template<typename T>
T* unwrapResource_impl(CEGUI::String name);

template<typename T>
T* unwrapResource(VALUE vobj,VALUE klass)
{
	try {
		if (rb_obj_is_kind_of(vobj, rb_cString)){
			return unwrapResource_impl<T>(wrap<CEGUI::String>(vobj));
		}else
			return unwrapResource_impl<T>(unwrapPtr<RubyResource>(vobj,klass)->name);
	}catch(CEGUI::Exception& e){
		rb_raise(e);
		return NULL;
	}

}

#endif /* CEGUIRESOURCE_HPP_ */
