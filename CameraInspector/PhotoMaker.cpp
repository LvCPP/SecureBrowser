#include "PhotoMaker.h"

namespace CameraInspector
{

PhotoMaker::PhotoMaker() : saver_(nullptr), curr_frame_{}
{
}

PhotoMaker::PhotoMaker(const std::shared_ptr<IFrameSaver>& saver) : saver_(saver), curr_frame_{}
{
}

void PhotoMaker::ProcessFrame(Frame frame)
{
	curr_frame_ = frame;
}

void PhotoMaker::MakePhoto() const
{
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
	saver_ = saver;
}

} // namespace CameraInspector