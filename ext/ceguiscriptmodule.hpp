#ifndef __RubyCeguiScriptModule_H__
#define __RubyCeguiScriptModule_H__

#include "main.hpp"
void Init_CeguiScriptModule(VALUE rb_mCegui);
extern VALUE rb_cCeguiScriptModule;

template <>
inline VALUE wrap< CEGUI::ScriptModule >(CEGUI::ScriptModule *scriptmodule )
{
	if(scriptmodule==NULL)
		return Qnil;
	return Data_Wrap_Struct(rb_cCeguiScriptModule, NULL, NULL, scriptmodule);
}
template <>
inline CEGUI::ScriptModule* wrap< CEGUI::ScriptModule* >(const VALUE &vscriptmodule)
{
	if (rb_obj_is_kind_of(vscriptmodule, rb_cCeguiScriptModule)){
		CEGUI::ScriptModule *scriptmodule;
		Data_Get_Struct( vscriptmodule, CEGUI::ScriptModule, scriptmodule);
		return scriptmodule;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cCeguiScriptModule),rb_obj_classname(vscriptmodule));
		return NULL;
	}
}
#endif /* __RubyCeguiScriptModule_H__ */
