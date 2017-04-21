#include "PhotoMaker.h"

namespace CameraInspector
{

PhotoMaker::PhotoMaker() : save_next_frame_(false), store_next_frame_(false)
		, saver_(nullptr), stored_frame_{}, mx_{}
{
}

PhotoMaker::PhotoMaker(const PhotoMaker& rhs) : save_next_frame_(false), store_next_frame_(false)
		, saver_(rhs.saver_), stored_frame_(rhs.stored_frame_), mx_{}
{
}

PhotoMaker::PhotoMaker(const std::shared_ptr<IFrameSaver>& saver) : save_next_frame_(false)
		, store_next_frame_(false), saver_(saver), stored_frame_{}, mx_{}
{
}

void PhotoMaker::ProcessFrame(Frame frame)
{
	if (save_next_frame_)
	{
		try
		{
			SaveToDisk(frame);
		}
		catch (std::exception ex)
		{
			save_next_frame_ = false;
			throw ex;
		}
	}
	else if (store_next_frame_)
	{
		stored_frame_.Remember(frame);
		store_next_frame_ = false;
	}
}

void PhotoMaker::MakePhoto()
{
	save_next_frame_ = true;
}

void PhotoMaker::StoreFrame()
{
	store_next_frame_ = true;
}

void PhotoMaker::SaveStoredFrame()
{
	SaveToDisk(stored_frame_);
}

void PhotoMaker::SetFrameSaver(const std::shared_ptr<IFrameSaver>& saver)
{
	std::lock_guard<std::mutex> guard(mx_);

	saver_ = saver;
}

Frame PhotoMaker::GetStoredFrame() const
{
	return stored_frame_;
}

void PhotoMaker::SaveToDisk(const Frame& frame) const
{
	std::lock_guard<std::mutex> guard(mx_);

	if (saver_)
	{
		saver_->Save(frame);
	}
	else
	{
		// Calling logger...
		throw std::exception("Saver is not initialized");
	}
}

} // namespace CameraInspector