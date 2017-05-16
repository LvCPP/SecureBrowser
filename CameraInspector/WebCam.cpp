#include "WebCam.h"

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