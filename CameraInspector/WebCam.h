#pragma once
#include "Frame.h"
#include "escapi.h"
#include <string> 

namespace CameraInspector
{

class WebCam
{
public:
	WebCam(std::string name, std::string unique_name, unsigned short id);
	
	void Initialize();
	void DeInitialize();
	
	Frame GetFrame();
	std::string GetName() const;
	std::string GetUniqueName() const;

private:	
	std::string name_;
	std::string unique_name_;
	unsigned short id_;
};

} //namespace CameraInspector