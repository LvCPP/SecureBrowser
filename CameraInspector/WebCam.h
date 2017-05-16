#pragma once
#include "Frame.h"
#include "escapi.h"
#include <string> 

namespace CameraInspector
{

class WebCam
{
public:
	void Initialize(SimpleCapParams& parameters)
	void DeInitialize();
	Frame MakeFrame();

private:
	std::string name_;
	unsigned short id_;
};

}