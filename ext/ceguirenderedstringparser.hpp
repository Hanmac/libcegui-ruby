/*
 * ceguirenderedstringparser.hpp
 *
 *  Created on: 03.12.2011
 *      Author: hanmac
 */
#ifndef __RubyCeguiRenderedStringParser_H__
#define __RubyCeguiRenderedStringParser_H__

#include "main.hpp"
#include "ceguirenderedstring.hpp"
#include "ceguifont.hpp"
#include "ceguicolorrect.hpp"
#include "ceguidefaultrenderedstringparser.hpp"
#include "ceguibasicrenderedstringparser.hpp"

void Init_CeguiRenderedStringParser(VALUE rb_mCegui);
extern VALUE rb_mCeguiRenderedStringParser;
//*
class RubyRenderedStringParser : public CEGUI::RenderedStringParser{

public:
	RubyRenderedStringParser(VALUE obj) : obj(obj){};
	virtual CEGUI::RenderedString parse(const CEGUI::String& input_string,
			CEGUI::Font* initial_font, const CEGUI::ColourRect* initial_colours)
	{
		return wrap<CEGUI::RenderedString>(rb_funcall(this->obj,rb_intern("parse"),3,wrap(input_string),wrap(initial_font),wrap(initial_colours)));
	}

	virtual ~RubyRenderedStringParser() {};
	VALUE obj;
};
//*/
extern std::map<VALUE, RubyRenderedStringParser*> renderedparserholder;

template <>
inline VALUE wrap< CEGUI::RenderedStringParser >(CEGUI::RenderedStringParser *parser )
{
	CEGUI::DefaultRenderedStringParser *defaultparser = dynamic_cast<CEGUI::DefaultRenderedStringParser*>(parser);
	if(defaultparser)
		return wrap(defaultparser);
	CEGUI::BasicRenderedStringParser *basicparser = dynamic_cast<CEGUI::BasicRenderedStringParser*>(parser);
	if(basicparser)
		return wrap(basicparser);

	std::map<VALUE,RubyRenderedStringParser*>::iterator it;
	for(it = renderedparserholder.begin();it != renderedparserholder.end();++it)
	{
	if(it->second == dynamic_cast<RubyRenderedStringParser*>(parser))
		return it->first;
	}

	return Qnil;
}

template <>
inline RubyRenderedStringParser* wrap< RubyRenderedStringParser* >(const VALUE &vparser)
{
	std::map<VALUE,RubyRenderedStringParser*>::iterator it = renderedparserholder.find(vparser);
	if(it != renderedparserholder.end()){
		return it->second;
	}else{
		RubyRenderedStringParser* temp = new RubyRenderedStringParser(vparser);
		renderedparserholder.insert(std::make_pair(vparser,temp));
		return temp;
	}
}

template <>
inline CEGUI::RenderedStringParser* wrap< CEGUI::RenderedStringParser* >(const VALUE &vparser)
{
	if (rb_obj_is_kind_of(vparser, rb_cCeguiDefaultRenderedStringParser))
		return wrap< CEGUI::DefaultRenderedStringParser* >(vparser);
	if (rb_obj_is_kind_of(vparser, rb_cCeguiBasicRenderedStringParser))
		return wrap< CEGUI::BasicRenderedStringParser* >(vparser);

	if (rb_obj_is_kind_of(vparser, rb_mCeguiRenderedStringParser)){
		return (CEGUI::RenderedStringParser*)wrap< RubyRenderedStringParser* >(vparser);
		return NULL;
	}else {
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_mCeguiRenderedStringParser),rb_obj_classname(vparser));
	}
}


#endif /* __RubyCeguiRenderedStringParser_H__ */

