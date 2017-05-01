#include "FaceDetector.h"
#include "Frame.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <memory>

using namespace CameraInspector;

namespace
{
constexpr char* CASCADE_FILE_PATH = "../Recources/haarcascade_frontalface_alt.xml";
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
	FaceDetectorImpl()
		:face_cascade_(CASCADE_FILE_PATH)
	{
	}
	cv::CascadeClassifier& GetFaceCascade() { return face_cascade_; }
private:
	cv::CascadeClassifier face_cascade_;
};

struct ObserverInfo
{
	static size_t GetPointerId(const std::shared_ptr<IFaceDetectorObserver>& observer)
	{
		return reinterpret_cast<size_t>(observer.get());
	}

	size_t id;
	std::weak_ptr<IFaceDetectorObserver> ptr;
};

FaceDetector::FaceDetector()
	: faces_quantity_(0)
	, pimpl_ (std::make_unique<FaceDetectorImpl>())
{
};

void FaceDetector::Attach(const std::shared_ptr<IFaceDetectorObserver>& observer)
{
	ObserverInfo temp { ObserverInfo::GetPointerId(observer), observer };
	observers_.emplace_back(temp);
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

void FaceDetector::Notify(int face_count)
{
	// Remove any dead observers.  These are ones which have expired().
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[](const ObserverInfo& o)
	{
		return o.ptr.expired();
	}), observers_.end());

	// Notify any valid observers of events.
	std::for_each(observers_.cbegin(), observers_.cend(),
		[face_count](const ObserverInfo& o)
	{
		auto observer = o.ptr.lock();
		if (observer) {
			observer->OnFaceQuantityChanged(face_count);
		}
	});
}

void FaceDetector::ProcessFrame(const Frame& frame)
{
	cv::Mat cv_frame = frame.GetImpl();
	cv::Mat frame_gray;

	cvtColor(cv_frame, frame_gray, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;
	// Detect faces
	pimpl_->GetFaceCascade().detectMultiScale(frame_gray, faces, SCALE_FACTOR, MIN_NEIGHBORS, FLAGS, cv::Size(30, 30));
	Notify(faces.size());
#ifdef DEBUG
	for (size_t ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
	{
		cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
		cv::Point pt2((faces[ic].x + faces[ic].width), (faces[ic].y + faces[ic].height));
		rectangle(cv_frame, pt1, pt2, COLOR_GREEN, THICKNESS, LINE_TYPE, SHIFT);
	}
imshow("Debug window", cv_frame);
#endif // DEBUG
}