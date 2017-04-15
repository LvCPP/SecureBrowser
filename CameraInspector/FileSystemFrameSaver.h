#pragma once
#include "IFrameSaver.h"

namespace CameraInspector
{

class FileSystemFrameSaver : public IFrameSaver
{
public:
	FileSystemFrameSaver();
	virtual ~FileSystemFrameSaver() = default;

	void Save(const cv::Mat& frame) override;
	void Save(const cv::Mat& frame, const std::string& name);
	void Save(const cv::Mat& frame, const std::string& name, const std::string& path);
	
	void SetPathToSave(const std::string& path);
	void SetNameToSave(const std::string& name);

private:
	// Does main work. Called from interface function
	static void SaveToDisk(const cv::Mat& frame, const std::string& name, const std::string& path);

	std::string name_to_save_;
	std::string path_to_save_;
};

} // namespace CameraInspector