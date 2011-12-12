#ifndef __RubyCeguiRect_H__
#define __RubyCeguiRect_H__

#include "ceguivector2.hpp"
void Init_CeguiRect(VALUE rb_mCegui);
extern VALUE rb_cCeguiRect;


template <>
inline VALUE wrap< CEGUI::Rectf >(CEGUI::Rectf *rect )
{
	return Data_Wrap_Struct(rb_cCeguiRect, NULL, free, rect);
}


template <>
inline bool is_wrapable< CEGUI::Rectf >(const VALUE &vrect)
{
	if(rb_obj_is_kind_of(vrect, rb_cCeguiRect)){
		return true;
	}else if(rb_respond_to(vrect,rb_intern("min")) &&
		rb_respond_to(vrect,rb_intern("max"))){
		return is_wrapable<CEGUI::Vector2f>(rb_funcall(vrect,rb_intern("min"),0))
				&& is_wrapable<CEGUI::Vector2f>(rb_funcall(vrect,rb_intern("max"),0));
	}else if(rb_respond_to(vrect,rb_intern("top")) &&
		rb_respond_to(vrect,rb_intern("bottom")) &&
		rb_respond_to(vrect,rb_intern("left")) &&
		rb_respond_to(vrect,rb_intern("right"))){
		return true;
	}else
		return false;
}


template <>
inline CEGUI::Rectf* wrap< CEGUI::Rectf* >(const VALUE &vrect)
{
	if(rb_obj_is_kind_of(vrect, rb_cCeguiRect)){
		CEGUI::Rectf *rect;
		Data_Get_Struct( vrect, CEGUI::Rectf, rect);
		return rect;
	}else if(rb_respond_to(vrect,rb_intern("min")) && 
	 rb_respond_to(vrect,rb_intern("max"))){
		CEGUI::Rectf *rect = new CEGUI::Rectf;
		rect->d_min = wrap<CEGUI::Vector2f>(rb_funcall(vrect,rb_intern("min"),0));
		rect->d_max = wrap<CEGUI::Vector2f>(rb_funcall(vrect,rb_intern("max"),0));
		return rect;

	}else if(rb_respond_to(vrect,rb_intern("top")) && 
	 rb_respond_to(vrect,rb_intern("bottom")) &&
	 rb_respond_to(vrect,rb_intern("left")) &&
	 rb_respond_to(vrect,rb_intern("right"))){
		CEGUI::Rectf *rect = new CEGUI::Rectf;
		rect->d_min.d_x = NUM2DBL(rb_funcall(vrect,rb_intern("top"),0));
		rect->d_min.d_y = NUM2DBL(rb_funcall(vrect,rb_intern("bottom"),0));
		rect->d_max.d_x = NUM2DBL(rb_funcall(vrect,rb_intern("left"),0));
		rect->d_max.d_y = NUM2DBL(rb_funcall(vrect,rb_intern("right"),0));
		return rect;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiRect),rb_obj_classname(vrect));
		return NULL;
	}
}
template <>
inline CEGUI::Rectf wrap< CEGUI::Rectf >(const VALUE &vrect)
{
	return *wrap< CEGUI::Rectf* >(vrect);
}
//*/
#endif /* __RubyCeguiRect_H__ */
