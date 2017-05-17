#pragma once

#include "WebCam.cpp"
#include "Frame.h"

#include "escapi.h"

#include <set>
#include <vector>
#include <string>

namespace CameraInspector
{

class WebCamController
{
	WebCamController();
	~WebCamController();

	std::set<std::string> ListNamesOfCameras() const;
	short GetCamerasCount() const noexcept;
	void ActivateCamera(std::string identifier);
	void ActivateCamera(std::string identifier, Relsolution resolution);
	
	Resolution GetResolution() const;
	Frame GetFrame();

private:
	std::vector<WebCam> cameras_;
	unsigned short activated_id_;
	SimpleCapParams camera_params_;
};

} // namespace CameraInspector