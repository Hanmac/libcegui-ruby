/*
 * ceguicomponentbase.cpp
 *
 *  Created on: 07.12.2011
 *      Author: hanmac
 */


#include "ceguicomponentbase.hpp"
#include "ceguicomponentarea.hpp"
#include "ceguifalagardenums.hpp"
#include "ceguiexception.hpp"

#include "ceguicolorrect.hpp"
#define _self wrap<CEGUI::FalagardComponentBase*>(self)
VALUE rb_cCeguiComponentBase;

namespace CeguiComponentBase
{

macro_attr(ComponentArea,CEGUI::ComponentArea)
macro_attr(Colours,CEGUI::ColourRect)

}
/*
 *
*/

void Init_CeguiComponentBase(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("CEGUI");

	rb_define_attr(rb_cCeguiComponentBase,"componentArea",1,1);
	rb_define_attr(rb_cCeguiComponentBase,"colors",1,1);

#endif

	using namespace CeguiComponentBase;
	rb_cCeguiComponentBase = rb_define_class_under(rb_mCegui,"ComponentBase",rb_cObject);
	rb_undef_alloc_func(rb_cCeguiComponentBase);

	rb_define_attr_method(rb_cCeguiComponentBase,"componentArea",_getComponentArea,_setComponentArea);
	rb_define_attr_method(rb_cCeguiComponentBase,"colors",_getColours,_setColours);


}

