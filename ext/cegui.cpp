#include "ceguicolor.hpp"
#include "ceguicolorrect.hpp"
#include "ceguivector2.hpp"
#include "ceguivector3.hpp"
#include "ceguiquaternion.hpp"

#include "ceguielement.hpp"
#include "ceguinamedelement.hpp"

#include "ceguiwindow.hpp"
#include "ceguitooltip.hpp"

#include "ceguidefaultwindow.hpp"
#include "ceguiframewindow.hpp"

#include "ceguilistboxitem.hpp"

#include "ceguifalagard.hpp"

#include "ceguiproperty.hpp"
#include "ceguipropertyset.hpp"

#include "ceguievent.hpp"
#include "ceguieventargs.hpp"
#include "ceguieventset.hpp"

#include "ceguivertex.hpp"

#include "ceguiwindoweventargs.hpp"
#include "ceguikeyeventargs.hpp"

#include "ceguiudim.hpp"
#include "ceguiuvector2.hpp"
#include "ceguiubox.hpp"
#include "ceguiurect.hpp"
#include "ceguiusize.hpp"

#include "ceguisize.hpp"
#include "ceguirect.hpp"

#include "ceguischeme.hpp"
#include "ceguifont.hpp"

#include "ceguiimage.hpp"

#include "ceguieventconnection.hpp"

#include "ceguixmlserializer.hpp"

#include "ceguiexception.hpp"

#include "ceguirenderer.hpp"

#include "ceguigeometrybuffer.hpp"
#include "ceguitexture.hpp"

#include "ceguirendertarget.hpp"

#include "ceguiresourceprovider.hpp"

#include "ceguisystem.hpp"
#include "ceguiimagecodec.hpp"

#include "ceguixmlparser.hpp"

#include "ceguixmlhandler.hpp"

#include "ceguiscriptmodule.hpp"

#include "ceguiwidgetlook.hpp"
#include "ceguicomponentbase.hpp"
#include "ceguicomponentarea.hpp"

#include "ceguitreeitem.hpp"

#include "ceguirenderedstring.hpp"
#include "ceguirenderedstringcomponent.hpp"
#include "ceguirenderedstringparser.hpp"

VALUE rb_mCegui;

VALUE Cegui_dummy0(VALUE self)
{
	return Qnil;
}
VALUE Cegui_dummy1(VALUE self,VALUE obj1)
{
	return Qnil;
}
VALUE Cegui_dummy2(VALUE self,VALUE obj1,VALUE obj2)
{
	return Qnil;
}
VALUE Cegui_dummy3(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3)
{
	return Qnil;
}
VALUE Cegui_dummy4(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3,VALUE obj4)
{
	return Qnil;
}

VALUE Cegui_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE methID,args;
	rb_scan_args(argc, argv, "1*",&methID,&args);
	if(rb_const_defined(self,SYM2ID(methID))){
		return rb_funcall2(rb_const_get(self,SYM2ID(methID)),rb_intern("new"),argc-1,RARRAY_PTR(args));
	}else {
		return rb_call_super(argc,argv);
	}
}


extern "C" void Init_cegui(void)
{
	rb_mCegui = rb_define_module("CEGUI");
	
	Init_CeguiColor(rb_mCegui);
	Init_CeguiColorRect(rb_mCegui);
	Init_CeguiVector2(rb_mCegui);
	Init_CeguiVector3(rb_mCegui);
	Init_CeguiVertex(rb_mCegui);
	Init_CeguiQuaternion(rb_mCegui);

	Init_CeguiUDim(rb_mCegui);
	Init_CeguiUVector2(rb_mCegui);
	Init_CeguiUBox(rb_mCegui);
	Init_CeguiURect(rb_mCegui);
	Init_CeguiUSize(rb_mCegui);
	
	Init_CeguiSize(rb_mCegui);
	Init_CeguiRect(rb_mCegui);

	Init_CeguiProperty(rb_mCegui);
	Init_CeguiPropertySet(rb_mCegui);

	Init_CeguiEvent(rb_mCegui);
	
	Init_CeguiEventSet(rb_mCegui);

	Init_CeguiEventConnection(rb_mCegui);


	Init_CeguiElement(rb_mCegui);
	Init_CeguiNamedElement(rb_mCegui);
	
	Init_CeguiWindow(rb_mCegui);
	Init_CeguiTooltip(rb_mCegui);
	Init_CeguiScrollbar(rb_mCegui);
	Init_CeguiListbox(rb_mCegui);
	Init_CeguiComboDropList(rb_mCegui);
	Init_CeguiItemEntry(rb_mCegui);
	Init_CeguiMenuItem(rb_mCegui);

	Init_CeguiDefaultWindow(rb_mCegui);
	Init_CeguiFrameWindow(rb_mCegui);

	Init_CeguiLayoutContainer(rb_mCegui);
	Init_CeguiSequentialLayoutContainer(rb_mCegui);
	Init_CeguiHorizontalLayoutContainer(rb_mCegui);
	Init_CeguiVerticalLayoutContainer(rb_mCegui);
	Init_CeguiGridLayoutContainer(rb_mCegui);

	Init_CeguiClippedContainer(rb_mCegui);
	Init_CeguiScrolledContainer(rb_mCegui);
	Init_CeguiDragContainer(rb_mCegui);

	Init_CeguiEditbox(rb_mCegui);
	
	Init_CeguiButtonBase(rb_mCegui);
	Init_CeguiPushButton(rb_mCegui);
	Init_CeguiThumb(rb_mCegui);
	Init_CeguiCheckbox(rb_mCegui);

	Init_CeguiListboxItem(rb_mCegui);
	Init_CeguiListboxTextItem(rb_mCegui);

	Init_CeguiItemListBase(rb_mCegui);
	Init_CeguiMenuBase(rb_mCegui);
	Init_CeguiPopupMenu(rb_mCegui);
	Init_CeguiMenubar(rb_mCegui);

	Init_CeguiScrolledItemListBase(rb_mCegui);

	Init_CeguiListHeader(rb_mCegui);
	Init_CeguiListHeaderSegment(rb_mCegui);

	Init_CeguiCombobox(rb_mCegui);
	Init_CeguiGroupBox(rb_mCegui);

	Init_CeguiSlider(rb_mCegui);
	Init_CeguiSpinner(rb_mCegui);
	Init_CeguiProgressBar(rb_mCegui);

	Init_CeguiTree(rb_mCegui);

	Init_CeguiTreeItem(rb_mCegui);

	Init_CeguiXMLSerializer(rb_mCegui);

	Init_CeguiScheme(rb_mCegui);
	Init_CeguiFont(rb_mCegui);
//	Init_CeguiImageset(rb_mCegui);
	Init_CeguiImage(rb_mCegui);

	Init_CeguiException(rb_mCegui);

	Init_CeguiRenderer(rb_mCegui);
	
	Init_CeguiGeometryBuffer(rb_mCegui);
	Init_CeguiTexture(rb_mCegui);

	Init_CeguiRenderTarget(rb_mCegui);
	Init_CeguiTextureTarget(rb_mCegui);
	
	Init_CeguiResourceProvider(rb_mCegui);
	Init_CeguiDefaultResourceProvider(rb_mCegui);
	
	Init_CeguiXMLParser(rb_mCegui);

	Init_CeguiXMLHandler(rb_mCegui);

	Init_CeguiSystem(rb_mCegui);
	Init_CeguiImageCodec(rb_mCegui);
	
	Init_CeguiScriptModule(rb_mCegui);
	
	Init_CeguiWidgetLook(rb_mCegui);
	Init_CeguiFalagard(rb_mCegui);

	Init_CeguiComponentArea(rb_mCegui);

	Init_CeguiComponentBase(rb_mCegui);
	Init_CeguiFrameComponent(rb_mCegui);
	
	Init_CeguiEventArgs(rb_mCegui);
	Init_CeguiWindowEventArgs(rb_mCegui);
	Init_CeguiKeyEventArgs(rb_mCegui);
	
	Init_CeguiRenderedString(rb_mCegui);
	Init_CeguiRenderedStringComponent(rb_mCegui);
	Init_CeguiRenderedStringTextComponent(rb_mCegui);
	Init_CeguiRenderedStringImageComponent(rb_mCegui);

	Init_CeguiRenderedStringParser(rb_mCegui);
	Init_CeguiDefaultRenderedStringParser(rb_mCegui);
	Init_CeguiBasicRenderedStringParser(rb_mCegui);
	VALUE array[4];
	array[0]=rb_str_new2("%d.%d.%d");
	array[1]=INT2NUM(CEGUI_VERSION_MAJOR);
	array[2]=INT2NUM(CEGUI_VERSION_MINOR);
	array[3]=INT2NUM(CEGUI_VERSION_PATCH);
	rb_const_set(rb_mCegui,rb_intern("Version"),rb_f_sprintf(4,array));

	rb_define_singleton_method(rb_mCegui,"method_missing",RUBY_METHOD_FUNC(Cegui_method_missing),-1);


}
