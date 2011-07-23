#ifndef __RubyCeguiRenderTarget_H__
#define __RubyCeguiRenderTarget_H__

#include "main.hpp"
void Init_CeguiRenderTarget(VALUE rb_mCegui);
extern VALUE rb_cCeguiRenderTarget;

#include "ceguitexturetarget.hpp"

template <>
inline VALUE wrap< CEGUI::RenderTarget >(CEGUI::RenderTarget *target )
{
	if(target==NULL)
		return Qnil;
	CEGUI::TextureTarget *textarget = dynamic_cast<CEGUI::TextureTarget*>(target);
	if(textarget)
		return wrap(textarget);
	return Data_Wrap_Struct(rb_cCeguiRenderTarget, NULL, NULL, target);
}

template <>
inline CEGUI::RenderTarget* wrap< CEGUI::RenderTarget* >(const VALUE &vtarget)
{
	if (rb_obj_is_kind_of(vtarget, rb_cCeguiRenderTarget)){
		CEGUI::RenderTarget *target;
		Data_Get_Struct( vtarget, CEGUI::RenderTarget, target);
		return target;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiRenderTarget),rb_obj_classname(vtarget));
		return NULL;
	}
}
#endif /* __RubyCeguiRenderTarget_H__ */
