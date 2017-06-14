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
			Save(frame);
		}
		catch (std::exception ex)
		{
			// Calling logger ...
			save_next_frame_ = false;
			throw;
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

void PhotoMaker::Save(const Frame& frame) const
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

std::shared_ptr<IFrameSaver> PhotoMaker::GetSaver() const
{
	return saver_;
}
