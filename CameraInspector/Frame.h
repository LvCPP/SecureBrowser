#pragma once
#include <memory>

namespace cv { class Mat; }

namespace CameraInspector
{

class Frame
{
public:
	Frame();
	Frame(int width, int height, void* data);
	virtual ~Frame() = default;
	
	void Construct(int width, int height, void* data);

	int GetCols() const;
	int GetRows() const;
	void* GetData() const;

protected:
	std::shared_ptr<cv::Mat> cv_mat_impl_;
};

} // namespace CameraInspector