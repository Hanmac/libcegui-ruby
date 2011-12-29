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
	return unwrapPtr<CEGUI::GeometryBuffer>(vgeometrybuffer, rb_cCeguiGeometryBuffer);
}
#endif /* __RubyCeguiGeometryBuffer_H__ */
