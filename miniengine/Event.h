#pragma once
#include <map>
#include <functional>
template<class ...Args>
class Event
{
private:
	unsigned int callbackCounter = 0;
	std::map<unsigned int, std::function<void(Args...)>> callbacks;
public:
	void addCallback(std::function<void(Args...)> callback)
	{
		callbackCounter++;
		callbacks[callbackCounter] = callback;
	}

	void broadcast(Args...args)
	{
		for (const auto& callback : callbacks)
		{
			callback.second(args...);
		}
	}
};