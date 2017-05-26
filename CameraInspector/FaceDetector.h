#pragma once
#include "IFrameHandler.h"
#include "IFaceDetectorObserver.h"
#include "Frame.h"
#include <vector>
#include <chrono>
#include <ctime>

class FaceDetectorImpl;// forward-declare private "implementation" class
struct ObserverInfo;

namespace CameraInspector
{

class FaceDetector : public IFrameHandler
{
public:
	FaceDetector();
	~FaceDetector() = default;
	void Attach(const std::shared_ptr<IFaceDetectorObserver>& observer);
	void Detach(const std::shared_ptr<IFaceDetectorObserver>& observer);
	void ProcessFrame(const Frame& frame) override;
	void SetFrequency(std::chrono::seconds frequency);
private:
	void Notify(int face_count);
	int faces_quantity_;
	std::chrono::seconds frequency_;
	std::chrono::steady_clock::time_point last_time_proceeded_;
	std::vector<ObserverInfo> observers_;
	std::unique_ptr<FaceDetectorImpl> pimpl_;
};

} // namespace CameraInspector