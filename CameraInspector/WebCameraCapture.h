#pragma once
#include "IFrameHandler.h"
#include "StableFrame.h"
#include "An.hpp"

#include <Windows.h>
#include <memory>
#include <vector>
#include <atomic>
#include <thread>

namespace cv { class VideoCapture; }

namespace CameraInspector
{

class WebCameraCapture
{
public:
	WebCameraCapture();

	WebCameraCapture(const WebCameraCapture&) = delete;
	WebCameraCapture(WebCameraCapture&&) = delete;
	WebCameraCapture& operator= (const WebCameraCapture&) = delete;
	WebCameraCapture& operator= (WebCameraCapture&&) = delete;

	void Start();
	void Stop();

	void AddFrameHandler(const std::shared_ptr<IFrameHandler>& handler);
	StableFrame GetCurrentStableFrame() const;
	
private:
	// TODO: make it thread-safe
	void ProcessHandlers();
	std::vector<std::shared_ptr<IFrameHandler>> handlers_;
	std::shared_ptr<cv::VideoCapture> camera_;
	std::atomic<bool> is_working_;
	std::thread worker_;
};

} // namespace CameraInspector

namespace Utils
{

template <>
inline void AnFill<CameraInspector::WebCameraCapture>(An<CameraInspector::WebCameraCapture>& an)
{
	static CameraInspector::WebCameraCapture wcc;
	an = &wcc;

	// Wait while camera initializes (don't need to do this on VS17)
	Sleep(500);
}

}