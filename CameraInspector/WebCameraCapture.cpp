#include "WebCameraCapture.h"
#include "WebCamController.h"
#include "Frame.h"

#include <Windows.h>

using namespace CameraInspector;
using namespace Utils;

WebCameraCapture::WebCameraCapture()
	: is_working_(false)
{
	WaitForInit();
}

void WebCameraCapture::Start()
{
	if (!is_working_)
	{
		is_working_ = true;
		worker_ = std::thread(&WebCameraCapture::ProcessHandlers, this);
	}
	else
	{
		throw std::exception("Capturing already started");
	}
}

void WebCameraCapture::Stop()
{
	if (is_working_)
	{
		is_working_ = false;
		if (worker_.joinable())
			worker_.join();
	}
	else
	{
		throw std::exception("Capturing already stopped");
	}
}

StableFrame WebCameraCapture::GetCurrentStableFrame() const
{
	return StableFrame(ReadFromCamera());
}

void WebCameraCapture::AddFrameHandler(const std::shared_ptr<IFrameHandler>& handler)
{
	handlers_.push_back(handler);
}

void WebCameraCapture::WaitForInit()
{
	while (ReadFromCamera().IsEmpty())
	{
		Sleep(0);
	}
}

Frame WebCameraCapture::ReadFromCamera()
{
	return An<WebCamController>()->GetActiveCamera().GetFrame();
}

void WebCameraCapture::ProcessHandlers()
{
	while (is_working_)
	{
		for (auto it = handlers_.begin(); it != handlers_.end(); ++it)
		{
			(*it)->ProcessFrame(ReadFromCamera());
		}
		Sleep(0);
	}
}

namespace Utils
{

template<> 
void AnFill<CameraInspector::WebCameraCapture>(An<CameraInspector::WebCameraCapture>& an)
{
	static CameraInspector::WebCameraCapture wcc;
	an = &wcc;
}

} // namespace Utils