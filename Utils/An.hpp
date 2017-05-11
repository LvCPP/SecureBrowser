#pragma once
#include <exception>

namespace Utils
{

template <typename T>
class An
{
public:
	An() { Clear(); }

	T& operator*() { return *Get0(); }
	T* operator->() { return Get0(); }
	const T* operator->() const { return Get0(); }
	void operator=(T* t) { data_ = t; }

	bool IsEmpty() const { return data_ == nullptr; }
	void Clear() { data_ = nullptr; }
	void Init() { if (IsEmpty()) Reinit(); }
	void Reinit() { AnFill(*this); }

private:
	T* Get0() const
	{
		const_cast<An*>(this)->Init();
		return data_;
	}

	T* data_;
};

template <typename T>
inline void AnFill(An<T>& an)
{
	static_assert(true, "Can't find implementation for class");
}

} // namespace Utils