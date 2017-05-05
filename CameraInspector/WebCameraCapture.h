#pragma once
#include "IFrameHandler.h"

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

	void Start();
	void Stop();
	// Frame handlers. This class instance can call they for different purposes
	void AddFrameHandler(const std::shared_ptr<IFrameHandler>& handler);

	cv::VideoCapture GetCamera() const noexcept;

private:
	// TODO: make it thread-safe
	void ProcessHandlers();

	std::vector<std::shared_ptr<IFrameHandler>> handlers_;
	std::shared_ptr<cv::VideoCapture> camera_;
	std::atomic<bool> is_working_;
	std::thread worker_;
};

} // namespace CameraInspector