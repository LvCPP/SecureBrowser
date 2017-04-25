#pragma once
#include "StableFrame.h"
#include "IFrameSaver.h"

namespace CameraInspector
{

// Store frame. Can represent and save it
class FrameStorer
{
public:
	FrameStorer(StableFrame frame);

	void Save(std::shared_ptr<IFrameSaver>& saver) const;

	const Frame& Get() const;

private:
	StableFrame stored_frame_;
};

} // namespace CameraInspector
