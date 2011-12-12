#ifndef __RubyCeguiTextureTarget_H__
#define __RubyCeguiTextureTarget_H__

#include "main.hpp"
void Init_CeguiTextureTarget(VALUE rb_mCegui);
extern VALUE rb_cCeguiTextureTarget;


template <>
inline VALUE wrap< CEGUI::TextureTarget >(CEGUI::TextureTarget *target )
{
	if(target==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiTextureTarget, NULL, NULL, target);
}

template <>
inline CEGUI::TextureTarget* wrap< CEGUI::TextureTarget* >(const VALUE &vtarget)
{
	if (rb_obj_is_kind_of(vtarget, rb_cCeguiTextureTarget)){
		CEGUI::TextureTarget *target;
		Data_Get_Struct( vtarget, CEGUI::TextureTarget, target);
		return target;
	}else{
		rb_raise(rb_eTypeError,"Excepted %s got %s!",rb_class2name(rb_cCeguiTextureTarget),rb_obj_classname(vtarget));
		return NULL;
	}
}
#endif /* __RubyCeguiTextureTarget_H__ */
