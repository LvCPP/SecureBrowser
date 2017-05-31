#pragma once
#include "CameraInspectorUtils.h"
#include <exception>

namespace CameraInspector
{

class CameraException : public std::exception
{
public:
	CI_API CameraException(const char* msg): message_(msg)
	{
	}

	CI_API virtual const char* what() const override
	{
		return message_;
	}

private:
	const char* message_;
};

} // namespace CameraInspector