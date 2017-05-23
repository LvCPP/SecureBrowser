#include "WebCamController.h"
#include <algorithm>
#include <sstream>

using namespace CameraInspector;

WebCamController::WebCamController()
	: is_activated_(false)
{
	unsigned short devices_count = setupESCAPI();
	Refresh();
}

WebCamController::~WebCamController()
{
	if (is_activated_)
		activated_camera_->DeInitialize();
}

std::vector<std::string> WebCamController::ListNamesOfCameras() const
{
	std::vector<std::string> names;

	for (WebCam wc: cameras_)
		names.push_back(wc.GetName());

	return names;
}

size_t WebCamController::GetCamerasCount() const noexcept
{
	return cameras_.size();
}

void WebCamController::ActivateCamera(std::string identifier)
{	
	if(is_activated_)
		activated_camera_->DeInitialize();
	
	activated_camera_ = std::find_if(cameras_.begin(), cameras_.end(), [&](WebCam cam)
	{
		return cam.GetName() == identifier;
	});
	
	activated_camera_->Initialize();
	
	is_activated_ = true;
}

WebCam WebCamController::GetActiveCamera() const
{
	return *activated_camera_;
}

void WebCamController::Refresh()
{
	if (is_activated_)
	{
		activated_camera_->DeInitialize();
		is_activated_ = false;
	}

	cameras_.clear();
	int devices_count = countCaptureDevices();
	int repeater = 0;

	for (auto i = 0; i < devices_count; ++i)
	{
		char temp[64];
		getCaptureDeviceName(i, temp, 64);
		std::string temp_str(temp);

		std::stringstream ss;
		ss << ++repeater << ": " << temp_str;
		temp_str = ss.str();

		cameras_.emplace_back(temp_str, i);
	}
}