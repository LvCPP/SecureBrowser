#pragma once

#include "WebCam.h"
#include "Frame.h"

#include "escapi.h"

#include <set>
#include <map>
#include <vector>
#include <string>

namespace CameraInspector
{

struct Resolution
{
	unsigned short width;
	unsigned short height;
};

class WebCamController
{
	WebCamController();
	~WebCamController();

	std::set<std::string> ListNamesOfCameras() const;
	size_t GetCamerasCount() const noexcept;
	void ActivateCamera(std::string identifier);
	void ActivateCamera(std::string identifier, Resolution resolution);
	
	Resolution GetResolution() const;
	Frame GetFrame();

private:
	std::map<std::string, unsigned short> camera_ids_;
	std::vector<WebCam> cameras_;
	unsigned short activated_id_;
	CameraParameters camera_params_;
};

} // namespace CameraInspector