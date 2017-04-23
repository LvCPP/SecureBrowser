#include "StableFrame.h"

#include <opencv2\highgui\highgui.hpp>

namespace CameraInspector
{

StableFrame::StableFrame() 
	: StableFrame(cv::Mat())
{
}

StableFrame::StableFrame(const StableFrame& sframe)
	: StableFrame(sframe.GetImpl())
{
}

StableFrame::StableFrame(const Frame& frame)
	: StableFrame(frame.GetImpl())
{
}

StableFrame::StableFrame(int width, int height, void* data) 
	: StableFrame(cv::Mat(height, width, CV_8UC3, data))
{
}

StableFrame::StableFrame(const cv::Mat& mat) 
	: Frame(mat)
{
	std::unique_ptr<cv::Mat> cpy = std::make_unique<cv::Mat>(cv_mat_impl_->clone());
	cv_mat_impl_ = std::move(cpy);
}

StableFrame& StableFrame::operator=(const StableFrame& sframe)
{
	std::unique_ptr<cv::Mat> cpy = std::make_unique<cv::Mat>(sframe.cv_mat_impl_->clone());
	cv_mat_impl_ = std::move(cpy);
	return *this;
}

} // namespace CameraInspector