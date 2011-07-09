#ifndef __RubyCeguiImageset_H__
#define __RubyCeguiImageset_H__

#include "main.hpp"
void Init_CeguiImageset(VALUE rb_mCegui);
extern VALUE rb_cCeguiImageset;

template <>
inline VALUE wrap< CEGUI::Imageset >(CEGUI::Imageset *imageset )
{
	if(imageset==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiImageset, NULL, NULL, imageset);
}
template <>
inline CEGUI::Imageset* wrap< CEGUI::Imageset* >(const VALUE &vimageset)
{
	if (rb_obj_is_kind_of(vimageset, rb_cString)){
		return &CEGUI::ImagesetManager::getSingletonPtr()->get(wrap<CEGUI::String>(vimageset));
	}else	if (rb_obj_is_kind_of(vimageset, rb_cCeguiImageset)){
		CEGUI::Imageset *imageset;
		Data_Get_Struct( vimageset, CEGUI::Imageset, imageset);
		return imageset;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiImageset),rb_obj_classname(vimageset));
		return NULL;
	}
}
#endif /* __RubyCeguiImageset_H__ */
