#include "WebCamController.h"
#include <algorithm>
#include <sstream>
#include <set>

using namespace CameraInspector;

static constexpr int DEFAULT_WIDTH = 640;
static constexpr int DEFAULT_HEIGHT = 480;

WebCamController::WebCamController()
	: activated_id_(-1)
	, camera_params_{ DEFAULT_WIDTH, DEFAULT_HEIGHT, std::make_unique<int[]>(DEFAULT_WIDTH * DEFAULT_HEIGHT)}
{
	unsigned short devices_count = setupESCAPI();
	unsigned short repeater = 0;

	for (auto i = 0; i < devices_count; ++i)
	{
		char temp[64];
		getCaptureDeviceName(i, temp, 64);
		std::string temp_str(temp);

		if (temp_str.find("USB") != std::string::npos)
		{
			std::stringstream ss;
			ss << temp_str << " (" << ++repeater << ")";
			temp_str = ss.str();
		}

		cameras_.emplace_back(temp_str, i);
		camera_ids_.emplace(temp_str, i);
	}
}

WebCamController::~WebCamController()
{
	// deinit lib
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
	if(activated_id_ != (unsigned short)-1)
		cameras_[activated_id_].DeInitialize();
	
	activated_id_ = camera_ids_[identifier];
	cameras_[activated_id_].Initialize(camera_params_);
}

void WebCamController::ActivateCamera(std::string identifier, Resolution resolution)
{
	camera_params_.width = resolution.width;
	camera_params_.height = resolution.height;
	ActivateCamera(identifier);
}

Resolution WebCamController::GetResolution() const
{
	return Resolution({ (unsigned short)camera_params_.width, (unsigned short)camera_params_.height });
}

Frame WebCamController::GetFrame()
{
	return cameras_[activated_id_].GetFrame(camera_params_);
}