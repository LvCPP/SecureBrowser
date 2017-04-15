#pragma once
#include "IFrameSaver.h"
#include "Frame.h"

#include <string>

namespace CameraInspector
{

class FileSystemFrameSaver : public IFrameSaver
{
public:
	FileSystemFrameSaver();
	virtual ~FileSystemFrameSaver() = default;

	void Save(const Frame& frame) override;
	void Save(const Frame& frame, const std::string& name);
	void Save(const Frame& frame, const std::string& name, const std::string& path);
	
	void SetPathToSave(const std::string& path);
	void SetNameToSave(const std::string& name);

private:
	// Does main work. Called from interface function
	static void SaveToDisk(const Frame& frame, const std::string& name, const std::string& path);

	std::string name_to_save_;
	std::string path_to_save_;
};

} // namespace CameraInspector