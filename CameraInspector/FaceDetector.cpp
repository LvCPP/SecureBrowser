#include "FaceDetector.h"
#include "Frame.h"

namespace CameraInspector
{
void FaceDetector::ProcessFrame(Frame frame)
{
	cv::Mat cv_frame(frame.GetRows(), frame.GetCols(), CV_8UC3, frame.GetData());
	cv::Mat frame_gray;

	cvtColor(cv_frame, frame_gray, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;
	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
	{
		cv::Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
		cv::Point pt2((faces[ic].x + faces[ic].width), (faces[ic].y + faces[ic].height));
		rectangle(cv_frame, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8, 0);
	}

	imshow("Debug window", cv_frame);
}

FaceDetector::FaceDetector()
	: face_cascade_name("../Recources/haarcascade_frontalface_alt.xml")
	, window_name("Capture - Face detection")
{
}

} // namespace CameraInspector