#pragma once
#include <exception>

namespace CameraInspector
{

class CameraException : public std::exception
{
public:
	CameraException(const char* msg): message_(msg)
	{
	}

	virtual const char* what() const override
	{
		return message_;
	}

private:
	const char* message_;
};

} // namespace CameraInspector