#Encoding: UTF-8
=begin
This file is part of libcegui-ruby. 

libcegui-ruby is a Ruby binding for the C++ library libcegui. 

Copyright © 2011 Hans Mackowiak

libcegui-ruby is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

libcegui-ruby is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with libcegui-ruby; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
=end

require 'mkmf'

#RbConfig::CONFIG["CC"] = RbConfig::CONFIG["CXX"]
#RbConfig::CONFIG["CPP"] = RbConfig::CONFIG["CXX"] + " -E"
#CONFIG["warnflags"] = RbConfig::CONFIG["warnflags"] = " -Wall"

dir_config("cegui")
with_cflags("-x c++"){
	unless(!pkg_config("CEGUI-NULL-0.8") && !pkg_config("CEGUI-OPENGL-0.8"))
		pkg_config("CEGUI-0.8")
	end
	unless(find_library("CEGUIBase","main") && find_header("CEGUI.h"))
		abort("need cegui-dev package.")
	end

	["Null","OpenGL"].each{|n|
		find_library("CEGUI#{n}Renderer","main")
		have_header("RendererModules/#{n}/Renderer.h")
	}

	#wird nicht mehr abgefagt weil das game das dynamisch laden soll
	#["Corona","DevIL","SILLY","TGA","STB","FreeImage"].each{|n|
	#	find_library("CEGUI#{n}ImageCodec","main")
	#	have_header("ImageCodecModules/#{n}ImageCodec/CEGUI#{n}ImageCodec.h")
	#}
	#["Expat","Libxml","Xerces","RapidXML","TinyXML"].each{|n|
	#	find_library("CEGUI#{n}Parser","main")
	#	have_header("XMLParserModules/#{n}Parser/CEGUI#{n}Parser.h")
	#}
	pkg_config("freetype2")
	find_header("freetype/config/ftheader.h")
	have_header("FreeTypeFont.h")

$CFLAGS += " -Wall"

$CFLAGS = $CFLAGS.split(" ").uniq.join(" ")
unless have_func("rb_string_value_cstr","ruby.h")
	abort("missing VALUE to char convert! You need ruby version >= 1.8.7")
end
unless have_macro("RETURN_ENUMERATOR","ruby.h")
	abort("missing RETURN_ENUMERATOR marco! You need ruby version >= 1.8.7")
end

create_header

create_makefile("cegui")

}
