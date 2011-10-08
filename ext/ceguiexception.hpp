#ifndef __RubyCeguiException_H__
#define __RubyCeguiException_H__

#include "main.hpp"
void Init_CeguiException(VALUE rb_mCegui);
extern VALUE rb_mCeguiException;
extern VALUE rb_eCeguiUnknownObjectException,rb_eCeguiAlreadyExistsException,rb_eCeguiInvalidRequestException;

template <>
inline VALUE wrap< CEGUI::UnknownObjectException >(CEGUI::UnknownObjectException *exception )
{
	return Data_Wrap_Struct(rb_eCeguiUnknownObjectException, NULL, free, exception);
}
template <>
inline VALUE wrap< CEGUI::AlreadyExistsException >(CEGUI::AlreadyExistsException *exception )
{
	return Data_Wrap_Struct(rb_eCeguiAlreadyExistsException, NULL, free, exception);
}
template <>
inline VALUE wrap< CEGUI::InvalidRequestException >(CEGUI::InvalidRequestException *exception )
{
	return Data_Wrap_Struct(rb_eCeguiInvalidRequestException, NULL, free, exception);
}


template <>
inline VALUE wrap< CEGUI::Exception >(const CEGUI::Exception &exception )
{
	const CEGUI::UnknownObjectException *unknownObject = dynamic_cast<const CEGUI::UnknownObjectException*>(&exception);
	if(unknownObject)
		return wrap(*unknownObject);
	const CEGUI::AlreadyExistsException *alreadyExists = dynamic_cast<const CEGUI::AlreadyExistsException*>(&exception);
	if(alreadyExists)
		return wrap(*alreadyExists);
	const CEGUI::InvalidRequestException *invalidRequest = dynamic_cast<const CEGUI::InvalidRequestException*>(&exception);
	if(invalidRequest)
		return wrap(*invalidRequest);
	return Qnil;
}


template <>
inline CEGUI::Exception* wrap< CEGUI::Exception* >(const VALUE &vexception)
{
	if(!rb_obj_is_kind_of(vexception, rb_mCeguiException))
		return NULL;
	CEGUI::Exception *exception;
  Data_Get_Struct( vexception, CEGUI::Exception, exception);
	return exception;
}

#endif /* __RubyCeguiException_H__ */
