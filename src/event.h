#ifndef CPP_EVENT_HEADER
#define CPP_EVENT_HEADER

#include <iostream>
#include <map>

#include "event_handler.h"
#include "event_handler_base.h"

typedef int MyEventHandler;

template <typename ReturnT>
class MyEvent
{
	typedef std::map<int,EventHandlerBase1<ReturnT> *> HandlersMap;
	HandlersMap m_handlers;
	int m_count;

public:

	MyEvent()
		: m_count(0) {}

	template <typename ListenerT>
	MyEventHandler attach(ListenerT* object, ReturnT (ListenerT::*member)())
	{
		typedef ReturnT (ListenerT::*PtrMember)();	
		m_handlers[m_count] = (new EventHandler1<ListenerT,ReturnT>(object,member));
		m_count++;	
		return m_count-1;
	}

	bool detach(MyEventHandler id)
	{
		HandlersMap::iterator it = m_handlers.find(id);

		if(it == m_handlers.end())
			return false;
		
		delete it->second;
		m_handlers.erase(it);				
		return true;
	}

	ReturnT notify()
	{
		HandlersMap::iterator it = m_handlers.begin();
		for(; it != m_handlers.end(); it++)
		{
			it->second->notify();
		}
	}
};

#endif
