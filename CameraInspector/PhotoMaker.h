#pragma once
#include "IFrameHandler.h"
#include "IFrameSaver.h"
#include "StableFrame.h"

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

	void ProcessFrame(const Frame& frame) override;
	// Save next frame
	void MakePhoto();
	// Store next frame
	void StoreFrame();
	// If user approves taken photo, save it to disk
	void SaveStoredFrame();

	// Making photos means saving them, so we need any class that can do it for us
	void SetFrameSaver(const std::shared_ptr<IFrameSaver>& saver);

	Frame GetStoredFrame() const;

private:
	void SaveToDisk(const Frame& frame) const;
	
	std::atomic<bool> save_next_frame_;
	std::atomic<bool> store_next_frame_;

	std::shared_ptr<IFrameSaver> saver_;
	StableFrame stored_frame_;
	mutable std::mutex mx_;
};

} // namespace CameraInspector