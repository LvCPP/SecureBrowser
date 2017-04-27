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
	const double SCALE_FACTOR = 1.1;
	const int MIN_NEIGHBORS = 2;
	const int FLAGS = cv::CASCADE_SCALE_IMAGE;
	const cv::Scalar COLOR = cv::Scalar(0, 255, 0);
	const int THICKNESS = 2;
	const int LINE_TYPE = 8;
	const int SHIFT = 0;
}

class Cascade
{
public:
	Cascade()
		:face_cascade_(CASCADE_FILE_PATH)
	{
	}
	cv::CascadeClassifier& GetFaceCascade() { return face_cascade_; }
private:
	cv::CascadeClassifier face_cascade_;
};

FaceDetector::FaceDetector()
	: pimpl (new Cascade())
{
};

void FaceDetector::Attach(IFaceDetectorObserver* observer)
{
	observers.push_back(observer);
}

void FaceDetector::Detach(IFaceDetectorObserver* observer)
{
	observers.remove(observer);
}

void FaceDetector::Notify(int face_count)
{
	for (IFaceDetectorObserver* obs : observers)
	{
		obs->OnFaceQuantityChanged(face_count);
	}
}

void FaceDetector::ProcessFrame(const Frame& frame)
{
	cv::Mat cv_frame = frame.GetImpl();
	cv::Mat frame_gray;

	cvtColor(cv_frame, frame_gray, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;
	// Detect faces
	pimpl->GetFaceCascade().detectMultiScale(frame_gray, faces, SCALE_FACTOR, MIN_NEIGHBORS, FLAGS, cv::Size(30, 30));
#ifdef DEBUG
	for (size_t ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
	{
		cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
		cv::Point pt2((faces[ic].x + faces[ic].width), (faces[ic].y + faces[ic].height));
		rectangle(cv_frame, pt1, pt2, COLOR, THICKNESS, LINE_TYPE, SHIFT);
	}
imshow("Debug window", cv_frame);
#endif // DEBUG
}