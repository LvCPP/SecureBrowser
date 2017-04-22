#pragma once
#include "Frame.h"

namespace CameraInspector
{

class StableFrame :
	public Frame
{
public:
	StableFrame();
	StableFrame(int width, int height, void* data);
	StableFrame(const Frame& frame);
	virtual ~StableFrame() = default;

	void Remember(const StableFrame& frame);
};

}