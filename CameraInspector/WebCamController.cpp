#include "WebCamController.h"
#include <algorithm>

using namespace CameraInspector;

static constexpr int DEFAULT_WIDTH = 640;
static constexpr int DEFAULT_HEIGHT = 480;

WebCamController::WebCamController()
	: activated_id_(-1)
	, camera_params_{ DEFAULT_WIDTH, DEFAULT_HEIGHT, std::make_unique<int[]>(DEFAULT_WIDTH * DEFAULT_HEIGHT)}
{
	unsigned short devices_count = setupESCAPI();

	for (auto i = 0; i < devices_count; ++i)
	{
		char temp[64];
		getCaptureDeviceName(i, temp, 64);
		cameras_.emplace_back(temp, i);
		std::string temp_str(temp);
		camera_ids_.emplace(temp_str, i);
	}
}

WebCamController::~WebCamController()
{
	// deinit lib
}

std::set<std::string> WebCamController::ListNamesOfCameras() const
{
	std::set<std::string> names;

	for (WebCam wc: cameras_)
		names.insert(wc.GetName());

	return names;
}

size_t WebCamController::GetCamerasCount() const noexcept
{
	return cameras_.size();
}

void WebCamController::ActivateCamera(std::string identifier)
{	
	cameras_[activated_id_].DeInitialize();
	activated_id_ = camera_ids_[identifier];
	cameras_[activated_id_].Initialize(camera_params_);
}

void WebCamController::ActivateCamera(std::string identifier, Resolution resolution)
{
	//TODO: Setup resol
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