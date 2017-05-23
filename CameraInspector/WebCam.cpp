#include "WebCam.h"

using namespace CameraInspector;

static constexpr int DEFAULT_WIDTH = 640;
static constexpr int DEFAULT_HEIGHT = 480;

inline CameraParameters& GetParameters()
{
	static CameraParameters params{ DEFAULT_WIDTH, DEFAULT_HEIGHT, std::make_unique<int[]>(DEFAULT_WIDTH * DEFAULT_HEIGHT) };
	return params;
}

WebCam::WebCam(std::string name, unsigned short id)
	: name_(name)
	, id_(id)
{
}

void WebCam::Initialize()
{
	initCapture(id_, &(SimpleCapParams)GetParameters());
}

Frame WebCam::GetFrame()
{
	doCapture(id_);
	CameraParameters& parameters(GetParameters());
	return Frame(parameters.width, parameters.height, reinterpret_cast<void*>(parameters.buffer.get()));
}

void WebCam::DeInitialize()
{
	deinitCapture(id_);
}

std::string WebCam::GetName() const
{
	return name_;
}