#pragma once
#include "IFrameHandler.h"
#include "IFrameSaver.h"

#include <memory>
#include <mutex>
#include <atomic>

namespace CameraInspector
{

class PhotoMaker : public IFrameHandler
{
public:
	CI_API PhotoMaker();
	CI_API PhotoMaker(const PhotoMaker& maker);
	CI_API PhotoMaker(const std::shared_ptr<IFrameSaver>& saver);
	CI_API virtual ~PhotoMaker() = default;

	// Calls <fps> times per second
	CI_API void ProcessFrame(const Frame& frame) override;
	// Save next frame
	CI_API void MakePhoto() noexcept;

	// Making photos means saving them, so we need any class that can do it for us
	CI_API void SetFrameSaver(const std::shared_ptr<IFrameSaver>& saver);
	CI_API std::shared_ptr<IFrameSaver> GetSaver() const;

private:
	void Save(const Frame& frame) const;
	
	std::atomic<bool> save_next_frame_;
	std::shared_ptr<IFrameSaver> saver_;
	mutable std::mutex mx_;
};

} // namespace CameraInspector