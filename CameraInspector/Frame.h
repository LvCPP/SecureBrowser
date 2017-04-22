#pragma once
#include <memory>

namespace cv { class Mat; }

namespace CameraInspector
{

class Frame
{
public:
	Frame();
	Frame(const cv::Mat& mat);
	Frame(int width, int height, void* data);
	virtual ~Frame() = default;
	
	void Construct(int width, int height, void* data);

	cv::Mat GetImpl() const;
	int GetCols() const;
	int GetRows() const;
	void* GetData() const;

protected:
	std::shared_ptr<cv::Mat> cv_mat_impl_;
};

} // namespace CameraInspector