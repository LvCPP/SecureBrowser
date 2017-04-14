#include "PhotoMaker.h"

namespace CameraInspector
{

PhotoMaker::PhotoMaker() : saver_(nullptr), curr_frame_{}
{
}

PhotoMaker::PhotoMaker(std::shared_ptr<IFrameSaver>& saver) : saver_(saver), curr_frame_{}
{
}

void PhotoMaker::ProcessFrame(cv::Mat frame)
{
	curr_frame_ = frame;
}

void PhotoMaker::MakePhoto() const
{
	if (saver_)
	{
		saver_->SaveFrame(curr_frame_);
	}
	else
	{
		throw std::exception("Saver is not initialized!");
	}
}

void PhotoMaker::MakePhoto(const cv::Mat& frame) const
{
	if (saver_)
	{
		saver_->SaveFrame(frame);
	}
	else
	{
		throw std::exception("Saver is not initialized!");
	}
}

void PhotoMaker::MakePhoto(const cv::Mat& frame, const std::string& name) const
{
	if (saver_)
	{
		saver_->SaveFrame(frame, name);
	}
	else
	{
		throw std::exception("Saver is not initialized!");
	}
}

void PhotoMaker::SetPhotoSaver(std::shared_ptr<IFrameSaver>& saver)
{
	saver_ = saver;
}

} // namespace CameraInspector