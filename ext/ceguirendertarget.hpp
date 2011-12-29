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
	return unwrapPtr<CEGUI::RenderTarget>(vtarget, rb_cCeguiRenderTarget);
}
#endif /* __RubyCeguiRenderTarget_H__ */
