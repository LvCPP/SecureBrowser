#pragma once
#include "CameraInspectorUtils.h"
#include <memory>

namespace cv { class Mat; }

namespace CameraInspector
{

class Frame
{
public:
	CI_API Frame();
	CI_API Frame(Frame&& frame);
	CI_API Frame(int width, int height, void* data);
	CI_API Frame(cv::Mat mat);
	CI_API Frame(std::shared_ptr<cv::Mat> impl);
	CI_API virtual ~Frame() = default;
	CI_API Frame& operator= (Frame&& rhs);
		
	CI_API bool IsEmpty() const;
	  
	CI_API cv::Mat GetImpl() const noexcept;
	CI_API int GetCols() const;
	CI_API int GetRows() const;
	CI_API void* GetData() const;

protected:
	std::shared_ptr<cv::Mat> cv_mat_impl_;
};

} // namespace CameraInspector