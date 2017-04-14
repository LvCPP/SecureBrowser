#include "WebCameraCapture.h"

namespace CameraInspector
{

void WebCameraCapture::Start()
{
}

void WebCameraCapture::Stop()
{
}

void WebCameraCapture::AddFrameHandler(std::shared_ptr<IFrameHandler>& handler)
{
	handlers_.push_back(std::move(handler));
}

} // namespace CameraInspector