#include "FileSystemFrameSaver.h"
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <Client.h>

constexpr int QUALITY_HIGH = 92;

using namespace CameraInspector;
using namespace Utils;
using namespace TCP_client;

FileSystemFrameSaver::FileSystemFrameSaver() 
	: name_to_save_("screenshot")
	, path_to_save_("")
{
}

void FileSystemFrameSaver::Save(const Frame& frame)
{
	SaveToDisk(frame, name_to_save_, path_to_save_);
	SaveToServer(name_to_save_, path_to_save_);
}

void FileSystemFrameSaver::Save(const Frame& frame, const std::string& name) const
{
	SaveToDisk(frame, name, path_to_save_);
	SaveToServer(name, path_to_save_);
}

void FileSystemFrameSaver::Save(const Frame& frame, const std::string& name, const std::string& path)
{
	SaveToDisk(frame, name, path);
	SaveToServer(name, path);
}

void FileSystemFrameSaver::SetPathToSave(const std::string& path) noexcept
{
	path_to_save_ = path;
}

void FileSystemFrameSaver::SetNameToSave(const std::string& name) noexcept
{
	name_to_save_ = name;
}

void FileSystemFrameSaver::SaveToDisk(const Frame& frame, const std::string& name, const std::string& path)
 {
	const cv::Mat cv_frame = frame.GetImpl();
	const std::vector<int> compression_params{ CV_IMWRITE_JPEG_QUALITY, QUALITY_HIGH };

	try
	{
		imwrite(path + name + ".jpg", cv_frame, compression_params);
	}
	catch (...)
	{
		// Calling logger ..
		throw std::exception("Problems with saving file");
	}
}

void CameraInspector::FileSystemFrameSaver::SaveToServer(const std::string& name, const std::string& path)
{
	An<Client>()->SendFile(path + name + ".jpg", "");
}