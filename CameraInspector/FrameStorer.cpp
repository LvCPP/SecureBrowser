#include "FrameStorer.h"

using namespace CameraInspector;

FrameStorer::FrameStorer(StableFrame sframe)
	: stored_frame_(sframe)
{
}

void FrameStorer::Save(std::shared_ptr<IFrameSaver>& saver) const
{
	if (saver)
	{
		saver->Save(dynamic_cast<const Frame&>(stored_frame_));
	}
	else
	{
		// Calling logger
		throw std::exception("Empty saver");
	}
}

const Frame& FrameStorer::Get() const
{
	return dynamic_cast<const Frame&>(stored_frame_);
}