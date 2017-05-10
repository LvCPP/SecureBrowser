#include "WebCameraCapture.h"
#include "Frame.h"

#include <opencv2\highgui\highgui.hpp>

using namespace CameraInspector;

WebCameraCapture::WebCameraCapture()
	: camera_(std::make_shared<cv::VideoCapture>(cv::VideoCapture(0)))
	, is_working_(false)
{
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

StableFrame WebCameraCapture::GetCurrentStableFrame() const
{
	cv::Mat r_mat;
	camera_->read(r_mat);
	return StableFrame(r_mat);
}

void WebCameraCapture::ProcessHandlers()
{
	while (is_working_)
	{
		cv::Mat mat_to_process;
		camera_->read(mat_to_process);

		for (auto it = handlers_.begin(); it != handlers_.end(); ++it)
		{
			(*it)->ProcessFrame(mat_to_process);
		}
		// I think we should unload the system by calling Sleep in this loop
	}
}