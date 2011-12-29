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
	return unwrapWindow<CEGUI::ScriptModule>(vscriptmodule, rb_cCeguiScriptModule);
}
#endif /* __RubyCeguiScriptModule_H__ */
