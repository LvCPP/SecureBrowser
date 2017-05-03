#include "StableFrame.h"

#include <opencv2\highgui\highgui.hpp>

using namespace CameraInspector;

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
{//tr
	cv_mat_impl_ = std::move(std::make_unique<cv::Mat>(cv_mat_impl_->clone()));
}

StableFrame& StableFrame::operator=(const StableFrame& sframe)
{
	if(this != &sframe)
		cv_mat_impl_ = std::move(std::make_unique<cv::Mat>(cv_mat_impl_->clone()));
	
	return *this;
}