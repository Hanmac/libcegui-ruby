#include "ceguicolor.hpp"
#include "ceguicolorrect.hpp"
#include "ceguivector2.hpp"
#include "ceguivector3.hpp"

#include "ceguiwindow.hpp"
#include "ceguitooltip.hpp"

#include "ceguifalagard.hpp"

#include "ceguiproperty.hpp"
#include "ceguipropertyset.hpp"

#include "ceguievent.hpp"
#include "ceguieventargs.hpp"
#include "ceguieventset.hpp"

#include "ceguivertex.hpp"

#include "ceguiudim.hpp"
#include "ceguiuvector2.hpp"
#include "ceguiubox.hpp"

#include "ceguisize.hpp"
#include "ceguirect.hpp"

#include "ceguischeme.hpp"
#include "ceguifont.hpp"

#include "ceguiimageset.hpp"

#include "ceguieventconnection.hpp"

#include "ceguixmlserializer.hpp"

#include "ceguiexception.hpp"

#include "ceguirenderer.hpp"
#include "ceguinullrenderer.hpp"
#include "ceguiopenglrenderer.hpp"

#include "ceguiresourceprovider.hpp"

#include "ceguisystem.hpp"

#include "ceguixmlparser.hpp"

#include "ceguiscriptmodule.hpp"

#include "ceguiwidgetlook.hpp"

VALUE rb_mCegui;

extern "C" void Init_cegui(void)
{
	rb_mCegui = rb_define_module("CEGUI");
	
	Init_CeguiColor(rb_mCegui);
	Init_CeguiColorRect(rb_mCegui);
	Init_CeguiVector2(rb_mCegui);
	Init_CeguiVector3(rb_mCegui);
	Init_CeguiVertex(rb_mCegui);

	Init_CeguiUDim(rb_mCegui);
	Init_CeguiUVector2(rb_mCegui);	
	Init_CeguiUBox(rb_mCegui);
	
	Init_CeguiSize(rb_mCegui);
	Init_CeguiRect(rb_mCegui);

	Init_CeguiProperty(rb_mCegui);
	Init_CeguiPropertySet(rb_mCegui);

	Init_CeguiEvent(rb_mCegui);
	Init_CeguiEventArgs(rb_mCegui);
	Init_CeguiEventSet(rb_mCegui);

	Init_CeguiEventConnection(rb_mCegui);

	Init_CeguiWindow(rb_mCegui);
	Init_CeguiTooltip(rb_mCegui);

	Init_CeguiXMLSerializer(rb_mCegui);

	Init_CeguiScheme(rb_mCegui);
	Init_CeguiFont(rb_mCegui);
	Init_CeguiImageset(rb_mCegui);

	Init_CeguiException(rb_mCegui);

	Init_CeguiRenderer(rb_mCegui);
	Init_CeguiNullRenderer(rb_mCegui);
	Init_CeguiOpenGLRenderer(rb_mCegui);
	
	Init_CeguiResourceProvider(rb_mCegui);
	Init_CeguiDefaultResourceProvider(rb_mCegui);
	
	Init_CeguiXMLParser(rb_mCegui);

	Init_CeguiSystem(rb_mCegui);
	
	Init_CeguiScriptModule(rb_mCegui);
	
	Init_CeguiWidgetLook(rb_mCegui);
	Init_CeguiFalagard(rb_mCegui);
	VALUE array[4];
	array[0]=rb_str_new2("%d.%d.%d");
	array[1]=INT2NUM(CEGUI_VERSION_MAJOR);
	array[2]=INT2NUM(CEGUI_VERSION_MINOR);
	array[3]=INT2NUM(CEGUI_VERSION_PATCH);
	rb_const_set(rb_mCegui,rb_intern("Version"),rb_f_sprintf(4,array));
}
