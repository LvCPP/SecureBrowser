#pragma once
#include "IFrameHandler.h"
#include "IFaceDetectorObserver.h"
#include "Frame.h"
#include <vector>
#include <memory>

class FaceDetectorImpl;// forward-declare private "implementation" class
struct ObserverInfo;

namespace CameraInspector
{

class FaceDetector : public IFrameHandler
{
public:
	CI_API FaceDetector();
	CI_API ~FaceDetector() = default;
	CI_API void Attach(const std::shared_ptr<IFaceDetectorObserver>& observer);
	CI_API void Detach(const std::shared_ptr<IFaceDetectorObserver>& observer);
	CI_API void ProcessFrame(const Frame& frame) override;
private:
	void Notify(int face_count);

	int faces_quantity_;
	std::vector<ObserverInfo> observers_;
	std::unique_ptr<FaceDetectorImpl> pimpl_;
};

} // namespace CameraInspector