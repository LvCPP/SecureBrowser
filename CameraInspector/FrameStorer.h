#pragma once
#include "StableFrame.h"
#include "IFrameSaver.h"

namespace CameraInspector
{

// Store frame. Can represent and save it
class FrameStorer
{
public:
	CI_API FrameStorer(StableFrame frame);

	CI_API void Save(std::shared_ptr<IFrameSaver>& saver) const;

	CI_API const Frame& Get() const;

private:
	StableFrame stored_frame_;
};

} // namespace CameraInspector
