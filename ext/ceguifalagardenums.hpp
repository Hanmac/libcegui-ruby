/*
 * ceguifalagardenums.hpp
 *
 *  Created on: 06.12.2011
 *      Author: hanmac
 */

#ifndef CEGUIFALAGARDENUMS_HPP_
#define CEGUIFALAGARDENUMS_HPP_

#include "main.hpp"
#include <CEGUI/falagard/XMLEnumHelper.h>

template <>
inline VALUE wrap< CEGUI::HorizontalTextFormatting >(const CEGUI::HorizontalTextFormatting &format )
{
	return ID2SYM(rb_intern(CEGUI::PropertyHelper<CEGUI::HorizontalTextFormatting>::toString(format).c_str()));
}

template <>
inline CEGUI::HorizontalTextFormatting wrap< CEGUI::HorizontalTextFormatting >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::PropertyHelper<CEGUI::HorizontalTextFormatting>::fromString(rb_id2name(SYM2ID(result)));
}

template <>
inline VALUE wrap< CEGUI::VerticalTextFormatting >(const CEGUI::VerticalTextFormatting &format )
{
	return ID2SYM(rb_intern(CEGUI::PropertyHelper<CEGUI::VerticalTextFormatting>::toString(format).c_str()));
}

template <>
inline CEGUI::VerticalTextFormatting wrap< CEGUI::VerticalTextFormatting >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::PropertyHelper<CEGUI::VerticalTextFormatting>::fromString(rb_id2name(SYM2ID(result)));
}


template <>
inline VALUE wrap< CEGUI::VerticalFormatting >(const CEGUI::VerticalFormatting &format )
{
	return ID2SYM(rb_intern(CEGUI::FalagardXMLHelper::vertFormatToString(format).c_str()));
}

template <>
inline CEGUI::VerticalFormatting wrap< CEGUI::VerticalFormatting >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::FalagardXMLHelper::stringToVertFormat(rb_id2name(SYM2ID(result)));
}


template <>
inline VALUE wrap< CEGUI::HorizontalFormatting >(const CEGUI::HorizontalFormatting &format )
{
	return ID2SYM(rb_intern(CEGUI::FalagardXMLHelper::horzFormatToString(format).c_str()));
}

template <>
inline CEGUI::HorizontalFormatting wrap< CEGUI::HorizontalFormatting >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::FalagardXMLHelper::stringToHorzFormat(rb_id2name(SYM2ID(result)));
}


template <>
inline VALUE wrap< CEGUI::DimensionType >(const CEGUI::DimensionType &format )
{
	return ID2SYM(rb_intern(CEGUI::FalagardXMLHelper::dimensionTypeToString(format).c_str()));
}

template <>
inline CEGUI::DimensionType wrap< CEGUI::DimensionType >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::FalagardXMLHelper::stringToDimensionType(rb_id2name(SYM2ID(result)));
}


template <>
inline VALUE wrap< CEGUI::FontMetricType >(const CEGUI::FontMetricType &format )
{
	return ID2SYM(rb_intern(CEGUI::FalagardXMLHelper::fontMetricTypeToString(format).c_str()));
}

template <>
inline CEGUI::FontMetricType wrap< CEGUI::FontMetricType >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::FalagardXMLHelper::stringToFontMetricType(rb_id2name(SYM2ID(result)));
}


template <>
inline VALUE wrap< CEGUI::DimensionOperator >(const CEGUI::DimensionOperator &format )
{
	return ID2SYM(rb_intern(CEGUI::FalagardXMLHelper::dimensionOperatorToString(format).c_str()));
}

template <>
inline CEGUI::DimensionOperator wrap< CEGUI::DimensionOperator >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::FalagardXMLHelper::stringToDimensionOperator(rb_id2name(SYM2ID(result)));
}


template <>
inline VALUE wrap< CEGUI::FrameImageComponent >(const CEGUI::FrameImageComponent &format )
{
	return ID2SYM(rb_intern(CEGUI::FalagardXMLHelper::frameImageComponentToString(format).c_str()));
}

template <>
inline CEGUI::FrameImageComponent wrap< CEGUI::FrameImageComponent >(const VALUE &vformat)
{
	VALUE result = rb_funcall(vformat,rb_intern("to_sym"),0);
	return CEGUI::FalagardXMLHelper::stringToFrameImageComponent(rb_id2name(SYM2ID(result)));
}

#endif /* CEGUIFALAGARDENUMS_HPP_ */
