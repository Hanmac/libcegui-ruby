#include "ceguivertex.hpp"
#include "ceguivector2.hpp"
#include "ceguivector3.hpp"
#include "ceguicolor.hpp"
#define _self wrap<CEGUI::Vertex*>(self)
VALUE rb_cCeguiVertex;

VALUE CeguiVertex_alloc(VALUE self)
{
	return wrap(new CEGUI::Vertex);
}
macro_attr_prop(Vertex,position,CEGUI::Vector3f)
macro_attr_prop(Vertex,tex_coords,CEGUI::Vector2f)
macro_attr_prop(Vertex,colour_val,CEGUI::Colour)
/*
*/
VALUE CeguiVertex_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	CeguiVertex_set_position(self,CeguiVertex_get_position(other));
	CeguiVertex_set_tex_coords(self,CeguiVertex_get_tex_coords(other));
	CeguiVertex_set_colour_val(self,CeguiVertex_get_colour_val(other));
	return result;
}
/*
 * call-seq:
 *   vertex.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE CeguiVertex_inspect(VALUE self)
{
	VALUE array[5];
	array[0]=rb_str_new2("#<%s:(%s, %s, %s)>");
	array[1]=rb_class_of(self);
	array[2]=CeguiVertex_get_position(self);
	array[3]=CeguiVertex_get_tex_coords(self);
	array[4]=CeguiVertex_get_colour_val(self);
	return rb_f_sprintf(5,array);
}
/*
 * call-seq:
 *   vector.hash -> Integer
 * 
 * hash from the combined vertex values.
 * ===Return value
 * Integer
*/
VALUE CeguiVertex_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiVertex_get_position(self));
	rb_ary_push(result,CeguiVertex_get_tex_coords(self));
	rb_ary_push(result,CeguiVertex_get_colour_val(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Vertex into an string.
*/
VALUE CeguiVertex_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,CeguiVertex_get_position(self));
	rb_ary_push(result,CeguiVertex_get_tex_coords(self));
	rb_ary_push(result,CeguiVertex_get_colour_val(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("sss"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Vertex.
*/
VALUE CeguiVertex_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("sss"));
	CeguiVertex_set_colour_val(self,rb_ary_pop(result));
	CeguiVertex_set_tex_coords(self,rb_ary_pop(result));
	CeguiVertex_set_position(self,rb_ary_pop(result));
	return self;
}

/*
 * Document-class: CEGUI::Vertex
 * 
 * This class represents an Vertex.
*/ 
void Init_CeguiVertex(VALUE rb_mCegui)
{
#if 0
	rb_mCegui = rb_define_module("Cegui");
	rb_define_attr(rb_cCeguiVertex,"position",1,1);
	rb_define_attr(rb_cCeguiVertex,"tex_coords",1,1);
	rb_define_attr(rb_cCeguiVertex,"colour_val",1,1);
#endif
	rb_cCeguiVertex = rb_define_class_under(rb_mCegui,"Vertex",rb_cObject);
	rb_define_alloc_func(rb_cCeguiVertex,CeguiVertex_alloc);
	rb_define_private_method(rb_cCeguiVertex,"initialize_copy",RUBY_METHOD_FUNC(CeguiVertex_initialize_copy),1);
	
	rb_define_attr_method(rb_cCeguiVertex,"position",CeguiVertex_get_position,CeguiVertex_set_position);
	rb_define_attr_method(rb_cCeguiVertex,"tex_coords",CeguiVertex_get_tex_coords,CeguiVertex_set_tex_coords);
	rb_define_attr_method(rb_cCeguiVertex,"colour_val",CeguiVertex_get_colour_val,CeguiVertex_set_colour_val);

	rb_define_method(rb_cCeguiVertex,"inspect",RUBY_METHOD_FUNC(CeguiVertex_inspect),0);
	rb_define_method(rb_cCeguiVertex,"hash",RUBY_METHOD_FUNC(CeguiVertex_hash),0);

	rb_define_method(rb_cCeguiVertex,"marshal_dump",RUBY_METHOD_FUNC(CeguiVertex_marshal_dump),0);
	rb_define_method(rb_cCeguiVertex,"marshal_load",RUBY_METHOD_FUNC(CeguiVertex_marshal_load),1);

}
