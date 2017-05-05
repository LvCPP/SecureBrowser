#include "WebCameraCapture.h"
#include "Frame.h"

#include <opencv2\highgui\highgui.hpp>

using namespace CameraInspector;

WebCameraCapture::WebCameraCapture()
	: camera_(std::make_shared<cv::VideoCapture>(cv::VideoCapture(0)))
	, is_working_(false)
{
}

WebCameraCapture& WebCameraCapture::Instance()
{
	// Since it's a static variable, if the class has already been created, it won't be created again.
	static WebCameraCapture inst;
	return inst;
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

void WebCameraCapture::AddFrameHandler(const std::shared_ptr<IFrameHandler>& handler)
{
	handlers_.push_back(handler);
}

cv::VideoCapture WebCameraCapture::GetCamera() const noexcept
{
	return *camera_;
}

void WebCameraCapture::ProcessHandlers()
{
	while (is_working_)
	{
		// I think we should unload the system by calling Sleep in this loop
		for (auto it = handlers_.begin(); it != handlers_.end(); ++it)
		{
			cv::Mat mat_to_process;
			camera_->read(mat_to_process);
			(*it)->ProcessFrame(mat_to_process);
		}
	}
}
