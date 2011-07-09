#ifndef __RubyCeguiRect_H__
#define __RubyCeguiRect_H__

#include "main.hpp"
void Init_CeguiRect(VALUE rb_mCegui);
extern VALUE rb_cCeguiRect;


template <>
inline VALUE wrap< CEGUI::Rect >(CEGUI::Rect *rect )
{
	return Data_Wrap_Struct(rb_cCeguiRect, NULL, free, rect);
}

template <>
inline CEGUI::Rect* wrap< CEGUI::Rect* >(const VALUE &vrect)
{
	if (rb_obj_is_kind_of(vrect, rb_cCeguiRect)){
		CEGUI::Rect *rect;
		Data_Get_Struct( vrect, CEGUI::Rect, rect);
		return rect;
	}else if(rb_respond_to(vrect,rb_intern("top")) && 
	 rb_respond_to(vrect,rb_intern("bottom")) &&
	 rb_respond_to(vrect,rb_intern("left")) &&
	 rb_respond_to(vrect,rb_intern("right"))){
	 	CEGUI::Rect *rect = new CEGUI::Rect;
	 	rect->d_top = NUM2DBL(rb_funcall(vrect,rb_intern("top"),0));
	 	rect->d_bottom = NUM2DBL(rb_funcall(vrect,rb_intern("bottom"),0));
	 	rect->d_left = NUM2DBL(rb_funcall(vrect,rb_intern("left"),0));
		rect->d_right = NUM2DBL(rb_funcall(vrect,rb_intern("right"),0));
	 	return rect;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiRect),rb_obj_classname(vrect));
		return NULL;
	}
}
template <>
inline CEGUI::Rect wrap< CEGUI::Rect >(const VALUE &vrect)
{
	return *wrap< CEGUI::Rect* >(vrect);
}
#endif /* __RubyCeguiRect_H__ */
