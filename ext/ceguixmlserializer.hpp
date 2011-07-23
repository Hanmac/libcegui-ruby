#ifndef __RubyCeguiXMLSerializer_H__
#define __RubyCeguiXMLSerializer_H__

#include "main.hpp"
#include "ceguiostream.hpp"
void Init_CeguiXMLSerializer(VALUE rb_mCegui);
extern VALUE rb_cCeguiXMLSerializer;


template <>
inline VALUE wrap< CEGUI::XMLSerializer >(CEGUI::XMLSerializer *xml )
{
	if(xml==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiXMLSerializer, NULL, NULL, xml);
}

template <>
inline CEGUI::XMLSerializer* wrap< CEGUI::XMLSerializer* >(const VALUE &vxml)
{
	if (rb_obj_is_kind_of(vxml, rb_cCeguiXMLSerializer)){
		CEGUI::XMLSerializer *xml;
		Data_Get_Struct( vxml, CEGUI::XMLSerializer, xml);
		return xml;
	}else{
		std::ostream *os = new std::ostream(new RubyStreamBuf(vxml));
		return new CEGUI::XMLSerializer(*os);
	}
}
#endif /* __RubyCeguiXMLSerializer_H__ */
