#include "WebCameraCapture.h"

namespace CameraInspector
{

void WebCameraCapture::Start()
{
}

void WebCameraCapture::Stop()
{
}

void WebCameraCapture::AddFrameHandler(const std::shared_ptr<IFrameHandler>& handler)
{
	handlers_.push_back(handler);
}

} // namespace CameraInspector