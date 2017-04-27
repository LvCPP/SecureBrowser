#pragma once
#include "IFrameHandler.h"
#include "IFaceDetectorObserver.h"
#include "Frame.h"
#include <list>

class Cascade;// forward-declare private "implementation" class

namespace CameraInspector
{

class FaceDetector : public IFrameHandler
{
public:
	FaceDetector();
	~FaceDetector() = default;
	void Attach(IFaceDetectorObserver* observer);
	void Detach(IFaceDetectorObserver* observer);
	void ProcessFrame(const Frame& frame) override;
private:
	void Notify(int face_count);

	std::list<IFaceDetectorObserver*> observers;
	std::unique_ptr<Cascade> pimpl;
};

} // namespace CameraInspector