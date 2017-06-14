#pragma once
#include "IFrameHandler.h"
#include "IFaceDetectorObserver.h"
#include "StableFrame.h"
#include <vector>
#include <memory>
#include <chrono>
#include <string>

class FaceDetectorImpl;// forward-declare private "implementation" class
struct ObserverInfo;

namespace CameraInspector
{

class FaceDetector : public IFrameHandler
{
public:
	CI_API FaceDetector(std::string path_to_resources);
	CI_API ~FaceDetector() = default;
	CI_API void Attach(const std::shared_ptr<IFaceDetectorObserver>& observer);
	CI_API void Detach(const std::shared_ptr<IFaceDetectorObserver>& observer);
	CI_API void ProcessFrame(const Frame& frame) override;
	CI_API void SetFrequency(std::chrono::seconds frequency);
	
private:
	void Notify(int face_count, StableFrame frame_to_save);

	int faces_quantity_;
	std::chrono::seconds frequency_;
	std::chrono::steady_clock::time_point last_time_proceeded_;
	std::vector<ObserverInfo> observers_;
	std::unique_ptr<FaceDetectorImpl> pimpl_;
};

} // namespace CameraInspector