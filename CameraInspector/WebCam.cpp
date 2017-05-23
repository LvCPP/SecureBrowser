#include "WebCam.h"

using namespace CameraInspector;

WebCam::WebCam(std::string name, unsigned short id)
	: name_(name)
	, id_(id)
{
}

void WebCam::Initialize(CameraParameters& parameters)
{
	initCapture(id_, &(SimpleCapParams)parameters);
}

Frame WebCam::GetFrame(CameraParameters& parameters)
{
	doCapture(id_);
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