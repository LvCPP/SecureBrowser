#include "WebCamController.h"
#include <algorithm>
#include <sstream>
#include <functional>
#include <exception>

using namespace CameraInspector;

WebCamController::WebCamController()
	: is_activated_(false)
{
	unsigned short devices_count = setupESCAPI();
	registerForDeviceNotification(std::bind(&WebCamController::Refresh, this));
	Refresh();
}

WebCamController::~WebCamController()
{
	unregisterForDeviceNotification();
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

const std::vector<WebCam>& WebCamController::GetCameras() const noexcept
{
	return cameras_;
}

size_t WebCamController::GetCamerasCount() const noexcept
{
	return cameras_.size();
}

void WebCamController::ActivateCamera(WebCam& camera)
{	
	if(is_activated_)
		activated_camera_->DeInitialize();
	
	activated_camera_ = std::find_if(cameras_.begin(), cameras_.end(), [&](WebCam cam)
	{
		return cam.GetName() == camera.GetName();
	});
	
	activated_camera_->Initialize();
	
	is_activated_ = true;
}

WebCam WebCamController::GetActiveCamera() const
{
	std::lock_guard<std::mutex> lock(mx);
	if (is_activated_)
		return *activated_camera_;
	else
		throw std::exception("Camera is refreshing now");
}

// TODO: flag
void WebCamController::Refresh()
{
	std::lock_guard<std::mutex> lock(mx);
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

	ActivateCamera(cameras_.at(0));
}