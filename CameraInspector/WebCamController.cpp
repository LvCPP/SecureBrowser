#include "WebCamController.h"

using namespace CAmeraInspector;

WebCamController::WebCamController()
	:
{
	unsigned short devices_count = setupESCAPI();
	
	SimpleCapParams params;

	params.mWidth = 640;
	params.mHeight = 480;
	params.mTargetBuf = new int[params.mWidth * params.mHeight];

	for (auto i = 0; i < devices_count; ++i)
	{
		cameras.push_back(params);

		char temp[256];
		getCaptureDeviceName(i, temp, 256);
		std::cout << "Device #" << i << ": " << temp << std::endl;
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

short WebCamController::GetCamerasCount() const noexcept
{
	return cameras_.size();
}

void WebCamController::ActivateCamera(std::string identifier)
{	
	std::vector<WebCam>::iterator iter = std::find_if(cameras_.begin(), cameras_.end(), [](const WebCam& wc) { return identifier == wc.GetName(); });
	size_t index = std::distance(cameras_.begin(), iter);
	if (index == cameras_.size())
	{
		throw std::exception("There's no such camera: " + iter);
	}
}

void WebCamController::ActivateCamera(std::string identifier, Relsolution resolution)
{
}

Resolution WebCamController::GetResolution() const
{
	return Resolution(camera_params_.mWidth, camera_params_.mHeight);
}

Frame WebCamController::GetFrame()
{
	return cameras_[activated_id_].GetFrame();
}