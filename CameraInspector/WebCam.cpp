#include "WebCam.h"
#include "CameraException.h"
#include "escapi.h"

using namespace CameraInspector;

static constexpr unsigned short DEFAULT_WIDTH = 640;
static constexpr unsigned short DEFAULT_HEIGHT = 480;

inline SimpleCapParams& GetParameters()
{
	static SimpleCapParams params{ new int [DEFAULT_WIDTH * DEFAULT_HEIGHT], DEFAULT_WIDTH, DEFAULT_HEIGHT };
	return params;
}

WebCam::WebCam(std::string name, std::string unique_name, unsigned short id)
	: name_(name)
	, unique_name_(unique_name)
	, id_(id)
{
}

void WebCam::Initialize() const
{
	if (initCapture(id_, &GetParameters()) == 0)
		throw CameraException("Initialization capture failed");
}

void WebCam::DeInitialize() const
{
	deinitCapture(id_);
}

Frame WebCam::GetFrame() const
{
	doCapture(id_);
	SimpleCapParams& parameters(GetParameters());
	return Frame(parameters.mWidth, parameters.mHeight, reinterpret_cast<void*>(parameters.mTargetBuf));
}

std::string WebCam::GetName() const
{
	return name_;
}

std::string WebCam::GetUniqueName() const
{
	return unique_name_;
}
