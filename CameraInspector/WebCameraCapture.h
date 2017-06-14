#pragma once
#include "IFrameHandler.h"
#include "StableFrame.h"
#include "An.hpp"

#include <memory>
#include <vector>
#include <atomic>
#include <thread>

namespace CameraInspector
{

class WebCameraCapture
{
public:
	CI_API WebCameraCapture();
	
	CI_API WebCameraCapture(const WebCameraCapture&) = delete;
	CI_API WebCameraCapture(WebCameraCapture&&) = delete;
	CI_API WebCameraCapture& operator= (const WebCameraCapture&) = delete;
	CI_API WebCameraCapture& operator= (WebCameraCapture&&) = delete;
	
	CI_API void Start();
	CI_API void Stop();

	static
	CI_API StableFrame GetCurrentStableFrame();
	
	CI_API void AddFrameHandler(const std::shared_ptr<IFrameHandler>& handler);
	
private:
	static Frame ReadFromCamera();
	static void WaitForInit();

	void ProcessHandlers();
	std::vector<std::shared_ptr<IFrameHandler>> handlers_;
	std::atomic<bool> is_working_;
	std::thread worker_;
};

} // namespace CameraInspector

namespace Utils
{

template<> CI_API void AnFill<CameraInspector::WebCameraCapture>(An<CameraInspector::WebCameraCapture>& an);

} // namespace CameraInspector