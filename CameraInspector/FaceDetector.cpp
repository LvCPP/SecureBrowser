#include "FaceDetector.h"
#include "StableFrame.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <memory>
#include <thread>

using namespace CameraInspector;

namespace
{
constexpr char* CASCADE_FILE = R"(haarcascade_frontalface_alt.xml)";
constexpr double SCALE_FACTOR = 1.1;
constexpr int MIN_NEIGHBORS = 2;
constexpr int FLAGS = cv::CASCADE_SCALE_IMAGE;
const cv::Scalar COLOR_GREEN = cv::Scalar(0, 255, 0);
constexpr int THICKNESS = 2;
constexpr int LINE_TYPE = 8;
constexpr int SHIFT = 0;
}

class FaceDetectorImpl
{
public:
	FaceDetectorImpl(std::string path_to_resources)
		:face_cascade_(path_to_resources + CASCADE_FILE)
	{
	}
	cv::CascadeClassifier& GetFaceCascade() { return face_cascade_; }

private:
	cv::CascadeClassifier face_cascade_;
};

struct ObserverInfo
{
	ObserverInfo(const std::shared_ptr<IFaceDetectorObserver>& observer)
		: id(GetPointerId(observer))
		, ptr(observer)
	{
	}


	static size_t GetPointerId(const std::shared_ptr<IFaceDetectorObserver>& observer)
	{
		return reinterpret_cast<size_t>(observer.get());
	}

	size_t id;
	std::weak_ptr<IFaceDetectorObserver> ptr;
};

FaceDetector::FaceDetector(std::string path_to_resources)
	: faces_quantity_(1)
	, frequency_(std::chrono::seconds(5))
	, last_time_proceeded_(std::chrono::high_resolution_clock::now())
	, pimpl_ (std::make_unique<FaceDetectorImpl>(path_to_resources))
{
};

void FaceDetector::Attach(const std::shared_ptr<IFaceDetectorObserver>& observer)
{
	observers_.emplace_back(observer);
}

void FaceDetector::Detach(const std::shared_ptr<IFaceDetectorObserver>& observer)
{
	const size_t temp_id = ObserverInfo::GetPointerId(observer);
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[temp_id](const ObserverInfo& o)
	{
		return o.id == temp_id;
	}), observers_.end());
}

void FaceDetector::Notify(int face_count, StableFrame frame_to_save)
{
	// Remove any dead observers.  These are ones which have expired().
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[](const ObserverInfo& o)
	{
		return o.ptr.expired();
	}), observers_.end());

	// Notify any valid observers of events.
	std::for_each(observers_.cbegin(), observers_.cend(),
		[&face_count, &frame_to_save](const ObserverInfo& o)
	{
		auto observer = o.ptr.lock();
		if (observer) {
			observer->OnFaceQuantityChanged(face_count, frame_to_save);
		}
	});
}

void FaceDetector::SetFrequency(std::chrono::seconds frequency)
{
	frequency_ = frequency;
}

void FaceDetector::ProcessFrame(const Frame& frame)
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	
	bool isTimeToProceed = std::chrono::duration_cast<std::chrono::seconds>
		(currentTime - last_time_proceeded_).count() > frequency_.count();

	if (!isTimeToProceed)
		return;

	last_time_proceeded_ = currentTime;
	cv::Mat cv_frame = frame.GetImpl();
	cv::Mat frame_gray;

	cvtColor(cv_frame, frame_gray, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;

	// Detect faces
	pimpl_->GetFaceCascade().detectMultiScale(frame_gray, faces, SCALE_FACTOR, MIN_NEIGHBORS, FLAGS, cv::Size(30, 30));

	const size_t new_faces_quantity = faces.size();
	if (new_faces_quantity != faces_quantity_)
		Notify(static_cast<int>(new_faces_quantity), frame);
}