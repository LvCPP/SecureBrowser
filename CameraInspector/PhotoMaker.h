#pragma once
#include "IFrameHandler.h"
#include "IFrameSaver.h"
#include <memory>

namespace CameraInspector
{

class PhotoMaker : public IFrameHandler
{
public:
	PhotoMaker();
	PhotoMaker(std::shared_ptr<IFrameSaver>& saver);
	virtual ~PhotoMaker() = default;

	// In this class processing means making photos from frames
	// Actually, just saving them
	// Interface function
	void ProcessFrame(cv::Mat frame) override;
	// Daoes main logic task of a class(makes photos). Called from interface function
	// Throw  when saver_ isn't initialized
	void MakePhoto() const;
	void MakePhoto(const cv::Mat& frame) const;
	void MakePhoto(const cv::Mat& frame, const std::string& name) const;
	// Making photos means saving them, so we need any class that can do it 4 us
	void SetPhotoSaver(std::shared_ptr<IFrameSaver>& saver);

private:
	std::shared_ptr<IFrameSaver> saver_;
	// Current frame that should be proceeded
	cv::Mat curr_frame_;
};

} // namespace CameraInspector