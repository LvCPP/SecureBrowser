#pragma once
#include "IFrameHandler.h"
#include "IFrameSaver.h"
#include "Frame.h"

#include <memory>
#include <mutex>
#include <atomic>

namespace CameraInspector
{

class PhotoMaker : public IFrameHandler
{
public:
	PhotoMaker();
	PhotoMaker(const PhotoMaker& rhs);
	PhotoMaker(const std::shared_ptr<IFrameSaver>& saver);
	virtual ~PhotoMaker() = default;

	// In this class processing means making photos from frames
	void ProcessFrame(Frame frame) override;
	// Does main logic task of a class(makes photos). Called from interface function
	// Throw std::exeption when saver_ isn't initialized
	void MakePhoto() const;
	// Makes photo without saving frame
	void MakePhoto(const Frame& frame) const;

	// Making photos means saving them, so we need any class that can do it for us
	void SetPhotoSaver(const std::shared_ptr<IFrameSaver>& saver);

private:
	std::shared_ptr<IFrameSaver> saver_;
	// Current frame that should be proceeded
	Frame curr_frame_;

	mutable std::mutex mx_;
};

} // namespace CameraInspector