#pragma once
#include <queue>
#include <mutex>

template<class T>
class MutexQueue
{
public:
	void Add(const T& element)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		queue_.push(element);
	}

	T Pop()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		if (queue_.empty())
		{
			throw std::out_of_range("queue is empty");
		}

		T temp(std::move(queue_.front()));
		queue_.pop();
		return temp;
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
