#pragma once
#include "WebCam.h"
#include "Frame.h"
#include <An.hpp>
#include "escapi.h"
#include <Windows.h>
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
public:
	WebCamController();
	~WebCamController();

	std::vector<std::string> ListNamesOfCameras() const;
	size_t GetCamerasCount() const noexcept;
	void ActivateCamera(std::string identifier);
	void ActivateCamera(std::string identifier, Resolution resolution);
	
	Resolution GetResolution() const;
	Frame GetFrame();
	void Refresh();

private:
	std::vector<WebCam> cameras_;
	std::vector<WebCam>::iterator activated_camera_;
	bool is_activated_;
	CameraParameters camera_params_;
};

} // namespace CameraInspector

namespace Utils
{

template <>
inline void AnFill<CameraInspector::WebCamController>(An<CameraInspector::WebCamController>& an)
{
	static CameraInspector::WebCamController wcc;
	an = &wcc;
}

} // namespace Utils