#pragma once
#include "IFrameSaver.h"

namespace CameraInspector
{

class FileSystemFrameSaver : public IFrameSaver
{
public:
	FileSystemFrameSaver();
	virtual ~FileSystemFrameSaver() = default;

	// Interface functions
	void SaveFrame(const cv::Mat& frame) override;
	void SaveFrame(const cv::Mat& frame, const std::string& name) override;
	void SaveFrame(const cv::Mat& frame, const std::string& name, const std::string& path);
	
	void SetPathToSaveFiles(const std::string& path);
	void SetNameOfSavingFile(const std::string& name);

private:
	// Does main work. Called from interface function
	void SaveToDisk(const cv::Mat& frame, const std::string& name, const std::string& path) const;

	// Current frame to be saved
	std::string name_to_save_;
	std::string path_to_save_;
};

} // namespace CameraInspector