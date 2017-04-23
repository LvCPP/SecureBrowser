#include "PhotoMaker.h"

using namespace CameraInspector;

PhotoMaker::PhotoMaker() 
	: save_next_frame_(false)
	, saver_(nullptr)
	, mx_()
{
}

PhotoMaker::PhotoMaker(const PhotoMaker& maker) 
	: save_next_frame_(false)
	, saver_(maker.saver_)
	, mx_()
{
}

PhotoMaker::PhotoMaker(const std::shared_ptr<IFrameSaver>& saver) 
	: save_next_frame_(false)
	, saver_(saver)
	, mx_()
{
}

void PhotoMaker::ProcessFrame(const Frame& frame)
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
		save_next_frame_ = false;
	}
}

void PhotoMaker::MakePhoto() noexcept
{
	save_next_frame_ = true;
}

void PhotoMaker::SetFrameSaver(const std::shared_ptr<IFrameSaver>& saver)
{
	std::lock_guard<std::mutex> guard(mx_);

	saver_ = saver;
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