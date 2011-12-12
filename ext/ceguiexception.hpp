#ifndef __RubyCeguiException_H__
#define __RubyCeguiException_H__

#include "main.hpp"
void Init_CeguiException(VALUE rb_mCegui);
extern VALUE rb_mCeguiException;
extern VALUE rb_eCeguiUnknownObjectException,rb_eCeguiAlreadyExistsException,rb_eCeguiInvalidRequestException;

template <>
inline VALUE wrap< CEGUI::UnknownObjectException >(CEGUI::UnknownObjectException *exception )
{
	return Data_Wrap_Struct(rb_eCeguiUnknownObjectException, NULL, NULL, exception);
}
template <>
inline VALUE wrap< CEGUI::AlreadyExistsException >(CEGUI::AlreadyExistsException *exception )
{
	return Data_Wrap_Struct(rb_eCeguiAlreadyExistsException, NULL, NULL, exception);
}
template <>
inline VALUE wrap< CEGUI::InvalidRequestException >(CEGUI::InvalidRequestException *exception )
{
	return Data_Wrap_Struct(rb_eCeguiInvalidRequestException, NULL, NULL, exception);
}


template <>
inline VALUE wrap< CEGUI::Exception >(CEGUI::Exception *exception )
{
	CEGUI::UnknownObjectException *unknownObject = dynamic_cast<CEGUI::UnknownObjectException*>(exception);
	if(unknownObject)
		return wrap(unknownObject);
	CEGUI::AlreadyExistsException *alreadyExists = dynamic_cast<CEGUI::AlreadyExistsException*>(exception);
	if(alreadyExists)
		return wrap(alreadyExists);
	CEGUI::InvalidRequestException *invalidRequest = dynamic_cast<CEGUI::InvalidRequestException*>(exception);
	if(invalidRequest)
		return wrap(invalidRequest);
	return Qnil;
}

inline void rb_raise(CEGUI::Exception &exception )
{
	return rb_raise(wrap(&exception));
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
