/*
 * ceguicomponentarea.cpp
 *
 *  Created on: 09.12.2011
 *      Author: hanmac
 */


/*
 * ceguiframecomponent.cpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */


#include "ceguicomponentarea.hpp"
#include "ceguiexception.hpp"

#define _self wrap<CEGUI::ComponentArea*>(self)
VALUE rb_cCeguiComponentArea;

namespace CeguiComponentArea
{
/*
 *
 */
VALUE _alloc(VALUE self)
{
	return wrap(new CEGUI::ComponentArea);
}

macro_attr(AreaPropertySource,CEGUI::String)

}
/*
 *
*/

void Init_CeguiComponentArea(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiComponentArea,"areaPropertySource",1,1);

#endif

	using namespace CeguiComponentArea;
	rb_cCeguiComponentArea = rb_define_class_under(rb_mCegui,"ComponentArea",rb_cObject);
	rb_define_alloc_func(rb_cCeguiComponentArea,_alloc);

	rb_define_attr_method(rb_cCeguiComponentArea,"areaPropertySource",_getAreaPropertySource,_setAreaPropertySource);


}



