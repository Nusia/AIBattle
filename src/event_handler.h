#pragma once

#include "event_handler_base.h"

template <typename ListenerT, typename ReturnT>
class EventHandler1 : public EventHandlerBase1<ReturnT>
{
	typedef ReturnT (ListenerT::*PtrMember)();
	ListenerT* m_object;
	PtrMember m_member;
	
public:

	EventHandler1(ListenerT* object, PtrMember member)
		: m_object(object), m_member(member)
	{}

	ReturnT notify()
	{
		return (m_object->*m_member)();		
	}	
};