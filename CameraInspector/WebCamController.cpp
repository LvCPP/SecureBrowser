#include "WebCamController.h"
#include <algorithm>
#include <sstream>

using namespace CameraInspector;

WebCamController::WebCamController()
	: is_activated_(false)
{
	unsigned short devices_count = setupESCAPI();
	registerForDeviceNotification(std::bind(&WebCamController::Refresh, this, std::placeholders::_1, true));
	Refresh();
}

WebCamController::~WebCamController()
{
	unregisterForDeviceNotification();
	if (is_activated_)
		activated_camera_->DeInitialize();
}

std::vector<WebCam>& WebCamController::GetCameras() noexcept
{
	return cameras_;
}

std::vector<std::string> WebCamController::ListNamesOfCameras() const
{
	std::vector<std::string> names;

	for (WebCam wc : cameras_)
		names.push_back(wc.GetName());

	return names;
}

size_t WebCamController::GetCamerasCount() const noexcept
{
	return cameras_.size();
}

void WebCamController::ActivateCamera(WebCam& camera)
{
	if (is_activated_)
		activated_camera_->DeInitialize();

	activated_camera_ = std::find_if(cameras_.begin(), cameras_.end(), [&](WebCam cam)
	{
		return cam.GetUniqueName() == camera.GetUniqueName();
	});

	activated_camera_->Initialize();

	is_activated_ = true;
}

WebCam WebCamController::GetActiveCamera() const
{
	std::lock_guard<std::mutex> lock(busy_);
	if (is_activated_)
		return *activated_camera_;
	else
		throw std::exception("Camera is not available right now");
}

void WebCamController::Refresh(bool is_arriving, bool is_from_lib)
{
	std::lock_guard<std::mutex> lock(busy_);
	std::string previous_camera_name("");
	if (is_activated_)
	{
		previous_camera_name = activated_camera_->GetUniqueName();
		activated_camera_->DeInitialize();
	}

	cameras_.clear();
	int devices_count = countCaptureDevices();

	for (auto i = 0; i < devices_count; ++i)
	{
		char temp[64];

		getCaptureDeviceName(i, temp, 64);
		std::string device_name_str(temp);

		getCaptureDeviceUniqueName(i, temp, 64);
		std::string unique_name_str(temp);

		cameras_.emplace_back(device_name_str, unique_name_str, i);
	}

	activated_camera_ = std::find_if(cameras_.begin(), cameras_.end(), [&](WebCam cam) -> bool
	{
		return cam.GetUniqueName() == previous_camera_name;
	});

	if (cameras_.empty())
		throw std::exception("No available cameras!");

	if (activated_camera_ == cameras_.end())
	{
		activated_camera_ = cameras_.begin();
	}

	if (is_from_lib)
		activated_camera_->Initialize();
}
