#include "WebCam.h"

using namespace CameraInspector;

static constexpr unsigned short DEFAULT_WIDTH = 640;
static constexpr unsigned short DEFAULT_HEIGHT = 480;

inline CameraParameters& GetParameters()
{
	static CameraParameters params{ DEFAULT_WIDTH, DEFAULT_HEIGHT, std::make_unique<int[]>(DEFAULT_WIDTH * DEFAULT_HEIGHT) };
	return params;
}

WebCam::WebCam(std::string name, std::string unique_name, unsigned short id)
	: name_(name)
	, unique_name_(unique_name)
	, id_(id)
{
}

void WebCam::Initialize()
{
	if (initCapture(id_, &(SimpleCapParams)GetParameters()) == 0)
		throw std::exception("Initialization capture failed");
}

void WebCam::DeInitialize()
{
	deinitCapture(id_);
}

Frame WebCam::GetFrame()
{
	doCapture(id_);
	CameraParameters& parameters(GetParameters());
	return Frame(parameters.width, parameters.height, reinterpret_cast<void*>(parameters.buffer.get()));
}

std::string WebCam::GetName() const
{
	return name_;
}

std::string WebCam::GetUniqueName() const
{
	return unique_name_;
}