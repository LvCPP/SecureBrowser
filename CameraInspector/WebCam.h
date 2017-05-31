#pragma once
#include "CameraInspectorUtils.h"
#include "Frame.h"
#include "escapi.h"
#include <string> 

namespace CameraInspector
{

class WebCam
{
public:
	CI_API WebCam(std::string name, std::string unique_name, unsigned short id);
	
	CI_API void Initialize();
	CI_API void DeInitialize();
	
	CI_API Frame GetFrame();
	CI_API std::string GetName() const;
	CI_API std::string GetUniqueName() const;

private:	
	std::string name_;
	std::string unique_name_;
	unsigned short id_;
};

} //namespace CameraInspector