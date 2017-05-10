#pragma once

#ifdef HTTPCLIENT_LIB
	#define HTTPCLIENT_API __declspec(dllexport) 
#else
	#define HTTPCLIENT_API __declspec(dllimport) 
#endif

