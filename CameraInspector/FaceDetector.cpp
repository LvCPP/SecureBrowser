#include "FaceDetector.h"
#include "Frame.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace
{
	const double scale_factor = 1.1;
	const int min_neighbors = 2;
	const int flags = cv::CASCADE_SCALE_IMAGE;
	const cv::Scalar color = cv::Scalar(0, 255, 0);
	const int thickness = 2;
	const int line_type = 8;
	const int shift = 0;
}

namespace CameraInspector
{
FaceDetector::FaceDetector()
	: face_cascade_name("../Recources/haarcascade_frontalface_alt.xml")
{
}


bool FaceDetector::Load()
{
	return face_cascade.load(face_cascade_name);
}

void FaceDetector::ProcessFrame(const Frame& frame)
{
	cv::Mat cv_frame = frame.GetImpl();
	cv::Mat frame_gray;

	cvtColor(cv_frame, frame_gray, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;
	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, scale_factor, min_neighbors, flags, cv::Size(30, 30));

	for (size_t ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
	{
		cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
		cv::Point pt2((faces[ic].x + faces[ic].width), (faces[ic].y + faces[ic].height));
		#ifdef DEBUG		
		rectangle(cv_frame, pt1, pt2, color, thickness, line_type, shift);
		#endif // DEBUG
	}
#ifdef DEBUG
imshow("Debug window", cv_frame);
#endif // DEBUG
}
} // namespace CameraInspector
