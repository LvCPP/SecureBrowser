#pragma once
#include "IFrameHandler.h"
#include "IFrameSaver.h"
#include "Frame.h"

#include <memory>

namespace CameraInspector
{

class PhotoMaker : public IFrameHandler
{
public:
	PhotoMaker();
	PhotoMaker(const std::shared_ptr<IFrameSaver>& saver);
	virtual ~PhotoMaker() = default;

	// In this class processing means making photos from frames
	// Actually, just saving them
	void ProcessFrame(Frame frame) override;
	// Daoes main logic task of a class(makes photos). Called from interface function
	// Throw  when saver_ isn't initialized
	void MakePhoto() const;
	void MakePhoto(const Frame& frame) const;
	// Making photos means saving them, so we need any class that can do it 4 us
	void SetPhotoSaver(const std::shared_ptr<IFrameSaver>& saver);

private:
	std::shared_ptr<IFrameSaver> saver_;
	// Current frame that should be proceeded
	Frame curr_frame_;
};

} // namespace CameraInspector