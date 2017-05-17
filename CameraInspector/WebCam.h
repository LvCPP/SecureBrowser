#pragma once
#include "Frame.h"
#include "escapi.h"
#include <string> 

namespace CameraInspector
{

class WebCam
{
public:
	WebCam(std::string name, unsigned short id);
	void Initialize(CameraParameters& parameters);
	Frame GetFrame(CameraParameters& parameters);
	void DeInitialize();
	std::string GetName() const;

private:
	std::string name_;
	unsigned short id_;
};

} //namespace CameraInspector