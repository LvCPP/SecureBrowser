#pragma once
#include "WebCam.h"
#include "Frame.h"
#include <An.hpp>
#include <vector>
#include <mutex>
#include <functional>

namespace CameraInspector
{

class WebCamController
{
public:
	CI_API WebCamController();

	CI_API std::vector<std::string> ListNamesOfCameras() const;
	CI_API void ActivateCamera(WebCam&);
	CI_API void Refresh(bool is_arriving = false);

	CI_API void RegisterForDeviceNotification();
	CI_API void UnregisterForDeviceNotification();

	CI_API void SetRefreshCallback(std::function<void()> callback);
	CI_API std::vector<WebCam>& GetCameras() noexcept;
	CI_API size_t GetCamerasCount() const noexcept;
	CI_API WebCam GetActiveCamera() const;

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

template <> CI_API void AnFill<CameraInspector::WebCamController>(An<CameraInspector::WebCamController>& an);

} // namespace Utils