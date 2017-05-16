#include "WebCam.h"

using namespace CameraInspector;

WebCam::WebCam()
	: name_(name)
	, id_(id)
{
}

void WebCam::Initialize(SimpleCapParams& parameters)
{
	initCapture(id_, &parameters);
}

Frame WebCam::GetFrame()
{
	doCapture(id_);
	return Frame(cam.mWidth, cam.mHeight, reinterpret_cast<void*>(cam.mTargetBuf));
}

void WebCam::DeInitialize()
{
	deinitCapture(id_);
}

std::string WebCam::GetName() const
{
	return name_;
}