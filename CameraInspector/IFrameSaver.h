#pragma once

namespace CameraInspector
{

class Frame;

class IFrameSaver
{
public:
	virtual ~IFrameSaver() = default;
	virtual void Save(const Frame& frame) = 0;
};

} // namespace CameraInspector