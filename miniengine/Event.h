#pragma once
#include <map>
#include <functional>

namespace mini
{
	template<class ...Args>
	class Event
	{
	private:
		unsigned int callbackCounter = 0;
		std::map<unsigned int, std::function<void(Args...)>> callbacks;
	public:
		//adds callback and returns its index
		unsigned int addCallback(std::function<void(Args...)> callback)
		{			
			callbacks[callbackCounter++] = callback;
			return callbackCounter;
		}

		void removeCallback(unsigned int callbackIndex)
		{
			callbacks.erase(callbackIndex);
		}

		void broadcast(Args...args)
		{
			for (const auto& callback : callbacks)
			{
				callback.second(args...);
			}
		}
	};
}