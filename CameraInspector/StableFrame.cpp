#include "StableFrame.h"

#include <opencv2\highgui\highgui.hpp>

namespace CameraInspector
{

StableFrame::StableFrame() : Frame::Frame()
{
}

StableFrame::StableFrame(int width, int height, void * data) : Frame::Frame(width, height, data)
{
}

StableFrame::StableFrame(const Frame& frame) : Frame::Frame(frame)
{
}

void StableFrame::Remember(const StableFrame& frame)
{
	std::unique_ptr<cv::Mat> cpy = std::make_unique<cv::Mat>(frame.cv_mat_impl_->clone());
	
	if (cv_mat_impl_)
		cv_mat_impl_.reset();

	cv_mat_impl_ = std::move(cpy);
}

}