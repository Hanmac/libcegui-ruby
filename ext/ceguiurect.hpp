#ifndef __RubyCeguiURect_H__
#define __RubyCeguiURect_H__

#include "main.hpp"
void Init_CeguiURect(VALUE rb_mCegui);
extern VALUE rb_cCeguiURect;

#include "ceguiuvector2.hpp"

template <>
inline VALUE wrap< CEGUI::URect >(CEGUI::URect *rect )
{
	return Data_Wrap_Struct(rb_cCeguiURect, NULL, free, rect);
}

template <>
inline bool is_wrapable< CEGUI::URect >(const VALUE &vrect)
{

	if(rb_obj_is_kind_of(vrect, rb_cCeguiURect)){
		return true;
	}else if(rb_respond_to(vrect,rb_intern("min")) &&
		rb_respond_to(vrect,rb_intern("max"))){
		return is_wrapable<CEGUI::UVector2>(rb_funcall(vrect,rb_intern("min"),0))
				&& is_wrapable<CEGUI::UVector2>(rb_funcall(vrect,rb_intern("max"),0));
	}else if(rb_respond_to(vrect,rb_intern("top")) &&
		rb_respond_to(vrect,rb_intern("bottom")) &&
		rb_respond_to(vrect,rb_intern("left")) &&
		rb_respond_to(vrect,rb_intern("right"))){

		return is_wrapable<CEGUI::UDim>(rb_funcall(vrect,rb_intern("top"),0)) &&
				is_wrapable<CEGUI::UDim>(rb_funcall(vrect,rb_intern("bottom"),0)) &&
				is_wrapable<CEGUI::UDim>(rb_funcall(vrect,rb_intern("left"),0)) &&
				is_wrapable<CEGUI::UDim>(rb_funcall(vrect,rb_intern("right"),0));
	}else
		return false;

}

template <>
inline CEGUI::URect* wrap< CEGUI::URect* >(const VALUE &vrect)
{
	if (rb_obj_is_kind_of(vrect, rb_cCeguiURect)){
		CEGUI::URect *box;
		Data_Get_Struct( vrect, CEGUI::URect, box);
		return box;
	}else if(rb_respond_to(vrect,rb_intern("min")) &&
	 rb_respond_to(vrect,rb_intern("max"))){
		CEGUI::URect *rect = new CEGUI::URect;
		rect->d_min = wrap<CEGUI::UVector2>(rb_funcall(vrect,rb_intern("min"),0));
		rect->d_max = wrap<CEGUI::UVector2>(rb_funcall(vrect,rb_intern("max"),0));
	 	return rect;
	}else if(rb_respond_to(vrect,rb_intern("top")) &&
	 rb_respond_to(vrect,rb_intern("bottom")) &&
	 rb_respond_to(vrect,rb_intern("left")) &&
	 rb_respond_to(vrect,rb_intern("right"))){
		CEGUI::URect *rect = new CEGUI::URect;
		rect->d_min.d_x = wrap<CEGUI::UDim>(rb_funcall(vrect,rb_intern("top"),0));
		rect->d_min.d_y = wrap<CEGUI::UDim>(rb_funcall(vrect,rb_intern("bottom"),0));
		rect->d_max.d_x = wrap<CEGUI::UDim>(rb_funcall(vrect,rb_intern("left"),0));
		rect->d_max.d_y = wrap<CEGUI::UDim>(rb_funcall(vrect,rb_intern("right"),0));
		return rect;

	}else{
		rb_raise(rb_eTypeError,"Expected %s got %s!",rb_class2name(rb_cCeguiURect),rb_obj_classname(vrect));
		return NULL;
	}

}
template <>
inline CEGUI::URect wrap< CEGUI::URect >(const VALUE &vrect)
{
	if (rb_obj_is_kind_of(vrect, rb_cString))
		return CEGUI::PropertyHelper<CEGUI::URect>::fromString(wrap<CEGUI::String>(vrect));
	else
		return *wrap< CEGUI::URect* >(vrect);
}
#endif /* __RubyCeguiURect_H__ */
