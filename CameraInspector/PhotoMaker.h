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
	PhotoMaker(const PhotoMaker& maker);
	PhotoMaker(const std::shared_ptr<IFrameSaver>& saver);
	virtual ~PhotoMaker() = default;

	// Calls <fps> times per second
	void ProcessFrame(const Frame& frame) override;
	// Save next frame
	void MakePhoto() noexcept;

	// Making photos means saving them, so we need any class that can do it for us
	void SetFrameSaver(const std::shared_ptr<IFrameSaver>& saver);

private:
	void Save(const Frame& frame) const;
	
	std::atomic<bool> save_next_frame_;
	std::shared_ptr<IFrameSaver> saver_;
	mutable std::mutex mx_;
};

} // namespace CameraInspector