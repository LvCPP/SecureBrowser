#include "Frame.h"

#include <opencv2/highgui/highgui.hpp>
	
using namespace CameraInspector;

Frame::Frame()
	: Frame(cv::Mat())
{
}

Frame::Frame(Frame&& frame)
	: Frame(move(frame.cv_mat_impl_))
{
}

Frame::Frame(int width, int height, void* data)
	: Frame(cv::Mat(height, width, CV_8UC4, data))
{
}

Frame::Frame(cv::Mat mat)
	: cv_mat_impl_(std::make_shared<cv::Mat>(cv::Mat(mat.rows, mat.cols, CV_8UC4, mat.data)))
{
}

Frame::Frame(std::shared_ptr<cv::Mat> impl)
	: cv_mat_impl_(impl)
{
}

Frame& Frame::operator=(Frame&& rhs) noexcept
{
	if (this == &rhs)
		return *this;

	try
	{
		cv_mat_impl_ = std::make_shared<cv::Mat>(std::move(rhs.GetImpl()));
	}
	catch(std::bad_alloc&)
	{
		// If std::bad_alloc exception is thrown, std::make_shared has no effect.	
	}

	return *this;
}

bool Frame::IsEmpty() const
{
	return cv_mat_impl_->data == nullptr;
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
