#include "Frame.h"

#include <opencv2\highgui\highgui.hpp>
	
using namespace CameraInspector;

Frame::Frame()
	: Frame(cv::Mat())
{
}

Frame::Frame(int width, int height, void* data)
	: Frame(cv::Mat(height, width, CV_8UC3, data))
{
}

Frame::Frame(cv::Mat mat)
	: cv_mat_impl_(std::make_shared<cv::Mat>(cv::Mat(mat.rows, mat.cols, CV_8UC3, mat.data)))
{
}

cv::Mat Frame::GetImpl() const noexcept
{
	return *cv_mat_impl_;
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