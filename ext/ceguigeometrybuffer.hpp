#ifndef __RubyCeguiGeometryBuffer_H__
#define __RubyCeguiGeometryBuffer_H__

#include "main.hpp"
void Init_CeguiGeometryBuffer(VALUE rb_mCegui);
extern VALUE rb_cCeguiGeometryBuffer;

template <>
inline VALUE wrap< CEGUI::GeometryBuffer >(CEGUI::GeometryBuffer *geometrybuffer )
{
	if(geometrybuffer==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiGeometryBuffer, NULL, NULL, geometrybuffer);
}

template <>
inline VALUE wrap< CEGUI::GeometryBuffer >(const CEGUI::GeometryBuffer &geometrybuffer )
{
	return wrap(&geometrybuffer);
}

template <>
inline CEGUI::GeometryBuffer* wrap< CEGUI::GeometryBuffer* >(const VALUE &vgeometrybuffer)
{
	if (rb_obj_is_kind_of(vgeometrybuffer, rb_cCeguiGeometryBuffer)){
		CEGUI::GeometryBuffer *geometrybuffer;
		Data_Get_Struct( vgeometrybuffer, CEGUI::GeometryBuffer, geometrybuffer);
		return geometrybuffer;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiGeometryBuffer),rb_obj_classname(vgeometrybuffer));
		return NULL;
	}
}
#endif /* __RubyCeguiGeometryBuffer_H__ */
