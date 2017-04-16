#include "PhotoMaker.h"

namespace CameraInspector
{

PhotoMaker::PhotoMaker() : saver_(nullptr), curr_frame_{}, mx_{}
{
}

PhotoMaker::PhotoMaker(const PhotoMaker& rhs) : saver_(rhs.saver_), curr_frame_(rhs.curr_frame_), mx_{}
{
}

PhotoMaker::PhotoMaker(const std::shared_ptr<IFrameSaver>& saver) : saver_(saver), curr_frame_{}, mx_{}
{
}

void PhotoMaker::ProcessFrame(Frame frame)
{
	std::lock_guard<std::mutex> locker(mx_);

	curr_frame_ = frame;
}

void PhotoMaker::MakePhoto() const
{
	std::lock_guard<std::mutex> locker(mx_);

	if (saver_)
	{
		saver_->Save(curr_frame_);
	}
	else
	{
		throw std::exception("Saver is not initialized!");
	}
}

void PhotoMaker::MakePhoto(const Frame& frame) const
{
	std::lock_guard<std::mutex> locker(mx_);

	if (saver_)
	{
		saver_->Save(frame);
	}
	else
	{
		throw std::exception("Saver is not initialized!");
	}
}

void PhotoMaker::SetPhotoSaver(const std::shared_ptr<IFrameSaver>& saver)
{
	std::lock_guard<std::mutex> locker(mx_);

	saver_ = saver;
}

} // namespace CameraInspector