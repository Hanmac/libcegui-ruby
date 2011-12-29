#ifndef __RubyCeguiEventConnection_H__
#define __RubyCeguiEventConnection_H__

#include "main.hpp"
void Init_CeguiEventConnection(VALUE rb_mCegui);
extern VALUE rb_cCeguiEventConnection;

struct RubyConnection{
	CEGUI::Event::Connection con;
};

template <>
inline VALUE wrap< CEGUI::Event::Connection >(const CEGUI::Event::Connection &connection )
{
	RubyConnection *temp = new RubyConnection;
	temp->con = connection;
	return Data_Wrap_Struct(rb_cCeguiEventConnection, NULL, NULL, temp);
}
template <>
inline CEGUI::Event::Connection wrap< CEGUI::Event::Connection >(const VALUE &vconnection)
{
	return unwrapPtr<RubyConnection>(vconnection, rb_cCeguiEventConnection)->con;
}
#endif /* __RubyCeguiEventConnection_H__ */
