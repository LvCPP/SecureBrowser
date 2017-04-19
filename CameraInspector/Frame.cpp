#include "Frame.h"

#include <opencv2\highgui\highgui.hpp>
	
namespace CameraInspector
{

Frame::Frame() : frame_(std::make_shared<cv::Mat>())
{
}

Frame::Frame(int width, int height, void* data) : Frame::Frame()
{
	frame_->cols = width;
	frame_->rows = height;
	frame_->data = reinterpret_cast<uchar*>(data);
}

void Frame::Construct(int width, int height, void* data)
{
	if(frame_)
		frame_.reset();
	
	frame_ = std::make_shared<cv::Mat>();

	frame_->cols = width;
	frame_->rows = height;
	frame_->data = reinterpret_cast<uchar*>(data);
}

int Frame::GetCols() const
{
	return frame_->cols;
}

int Frame::GetRows() const
{
	return frame_->rows;
}

void* Frame::GetData() const
{
	return frame_->data;
}

} // namespace CameraInspector
