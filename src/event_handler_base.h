#pragma once

template <typename ReturnT>
class EventHandlerBase1
{
public:
	virtual ReturnT notify() = 0;
};