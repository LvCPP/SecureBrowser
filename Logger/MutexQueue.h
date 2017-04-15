#pragma once
#include <queue>
#include <mutex>

template<class T>
class MutexQueue
{
public:
	void Add(T element)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		queue_.push(element);
	}

	T Pop()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		if (!queue_.empty())
		{
			T temp(queue_.front());
			queue_.pop();
			return temp;
		}
		else
		{
			throw std::runtime_error("queue is empty");
		}
	}

	bool IsEmpty() const
	{
		std::unique_lock<std::mutex> lock(mutex_);
		return queue_.empty();
	}

private:
	std::queue<T> queue_;
	mutable std::mutex mutex_;
};
