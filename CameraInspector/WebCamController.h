#pragma once
#include "WebCam.h"
#include "Frame.h"
#include <An.hpp>
#include "escapi.h"
#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include <mutex>

namespace CameraInspector
{

class WebCamController
{
public:
	WebCamController();
	~WebCamController();

	std::vector<WebCam>& GetCameras() noexcept;
	std::vector<std::string> ListNamesOfCameras() const;
	size_t GetCamerasCount() const noexcept;
	void ActivateCamera(WebCam&);

	void Refresh(bool b = false, bool is_from_lib = false);
	WebCam GetActiveCamera() const;

private:
	std::vector<WebCam> cameras_;
	std::vector<WebCam>::iterator activated_camera_;
	bool is_activated_;
	mutable std::mutex busy_;
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