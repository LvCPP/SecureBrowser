#pragma once
#include "IFrameSaver.h"
#include "Frame.h"

#include <string>

namespace CameraInspector
{

class FileSystemFrameSaver : public IFrameSaver
{
public:
	CI_API FileSystemFrameSaver();
	CI_API virtual ~FileSystemFrameSaver() = default;

	CI_API void Save(const Frame& frame) override;
	CI_API void Save(const Frame& frame, const std::string& name) const;
	static
	CI_API void Save(const Frame& frame, const std::string& name, const std::string& path);
	
	CI_API void SetPathToSave(const std::string& path) noexcept;
	CI_API void SetNameToSave(const std::string& name) noexcept;

private:
	static void SaveToDisk(const Frame& frame, const std::string& name, const std::string& path);
	static void SaveToServer(const std::string& name, const std::string& path);

	std::string name_to_save_;
	std::string path_to_save_;
};

} // namespace CameraInspector