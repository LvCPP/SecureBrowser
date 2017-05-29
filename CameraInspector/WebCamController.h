#pragma once
#include "WebCam.h"
#include "Frame.h"
#include <An.hpp>
#include "escapi.h"
#include <vector>
#include <string>
#include <mutex>
#include <functional>

namespace CameraInspector
{

class WebCamController
{
public:
	WebCamController();
	~WebCamController();

	std::vector<std::string> ListNamesOfCameras() const;
	void ActivateCamera(WebCam&);
	void Refresh(bool is_arriving = false);
	
	void SetRefreshCallback(std::function<void()> callback);
	std::vector<WebCam>& GetCameras() noexcept;
	size_t GetCamerasCount() const noexcept;
	WebCam GetActiveCamera() const;

private:
	std::vector<WebCam> cameras_;
	std::vector<WebCam>::iterator activated_camera_;
	std::function<void()> callback_;
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