#include "FileSystemFrameSaver.h"

constexpr int QUALITY_HIGH = 92;

namespace CameraInspector
{

FileSystemFrameSaver::FileSystemFrameSaver() : name_to_save_("screenshot"), path_to_save_("")
{
}

void FileSystemFrameSaver::SaveFrame(const cv::Mat& frame)
{
	SaveToDisk(frame, name_to_save_, path_to_save_);
}

void FileSystemFrameSaver::SaveFrame(const cv::Mat& frame, const std::string& name)
{
	SaveToDisk(frame, name, path_to_save_);
}

void FileSystemFrameSaver::SaveFrame(const cv::Mat& frame, const std::string& name, const std::string& path)
{
	SaveToDisk(frame, name, path);
}

void FileSystemFrameSaver::SetPathToSaveFiles(const std::string& path)
{
	path_to_save_ = path;
}

void FileSystemFrameSaver::SetNameOfSavingFile(const std::string& name)
{
	name_to_save_ = name;
}

void FileSystemFrameSaver::SaveToDisk(const cv::Mat& frame, const std::string& name, const std::string& path) const
{
	std::vector<int> compression_params{ CV_IMWRITE_JPEG_QUALITY, QUALITY_HIGH };

	try
	{
		imwrite(path + name + ".jpg", frame, compression_params);
	}
	catch (...)
	{
		// Calling logger ..
		throw std::exception("Problems with saving file");
	}
}

} // namespace CameraInspector