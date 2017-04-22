#include "Frame.h"

#include <opencv2\highgui\highgui.hpp>
	
namespace CameraInspector
{

Frame::Frame() : cv_mat_impl_(std::make_shared<cv::Mat>(cv::Mat{}))
{
}

Frame::Frame(int width, int height, void* data) 
		: cv_mat_impl_(std::make_shared<cv::Mat>(cv::Mat{ height, width, CV_8UC3, data }))
{
}

void Frame::Construct(int width, int height, void* data)
{
	if(cv_mat_impl_)
		cv_mat_impl_.reset();
	
	cv_mat_impl_ = std::make_shared<cv::Mat>(cv::Mat{ height, width, CV_8UC3, data });
}

int Frame::GetCols() const
{
	return cv_mat_impl_->cols;
}

int Frame::GetRows() const
{
	return cv_mat_impl_->rows;
}

void* Frame::GetData() const
{
	return cv_mat_impl_->data;
}

} // namespace CameraInspector