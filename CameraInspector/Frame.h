#pragma once
#include <memory>

namespace cv { class Mat; }

namespace CameraInspector
{

class Frame
{
public:
	Frame();
	Frame(Frame&& frame);
	Frame(int width, int height, void* data);
	Frame(cv::Mat mat);
	Frame(std::shared_ptr<cv::Mat> impl);
	virtual ~Frame() = default;
	
	cv::Mat GetImpl() const noexcept;
	
	int GetCols() const;
	int GetRows() const;
	void* GetData() const;

protected:
	std::shared_ptr<cv::Mat> cv_mat_impl_;
};

} // namespace CameraInspector