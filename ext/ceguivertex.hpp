#ifndef __RubyCeguiVertex_H__
#define __RubyCeguiVertex_H__

#include "main.hpp"
void Init_CeguiVertex(VALUE rb_mCegui);
extern VALUE rb_cCeguiVertex;


template <>
inline VALUE wrap< CEGUI::Vertex >(CEGUI::Vertex *vertex )
{
	return Data_Wrap_Struct(rb_cCeguiVertex, NULL, free, vertex);
}

template <>
inline CEGUI::Vertex* wrap< CEGUI::Vertex* >(const VALUE &vvertex)
{
	if (rb_obj_is_kind_of(vvertex, rb_cCeguiVertex)){
		CEGUI::Vertex *vertex;
		Data_Get_Struct( vvertex, CEGUI::Vertex, vertex);
		return vertex;
	}else{ //TODO add struct support later
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiVertex),rb_obj_classname(vvertex));
		return NULL;
	}
}
template <>
inline CEGUI::Vertex wrap< CEGUI::Vertex >(const VALUE &vvertex)
{
	return *wrap< CEGUI::Vertex* >(vvertex);
}
#endif /* __RubyCeguiVertex_H__ */
