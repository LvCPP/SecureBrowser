#pragma once
#include "IFrameHandler.h"

namespace CameraInspector
{

class FaceDetector : public IFrameHandler
{
public:
	virtual ~FaceDetector() = default;

	// Interface :). Calls 'work' function inside
	void ProcessFrame(Frame frame) override;
};

} // namespace CameraInspector