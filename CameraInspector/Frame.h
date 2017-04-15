#pragma once

namespace CameraInspector
{

class Frame
{
public:
	Frame() = default;
	//Mat(Size size, int type, void *data, size_t step = AUTO_STEP)
	Frame(int height, int width, void* data);			// QImage|cv::Mat to frame
	
	void Construct(int height, int width, void* data);

	int GetRows() const;
	int GetCols() const;
	void* GetData() const;

private:
	int cols_;		
	int rows_;		
	void* data_;	
};

} // namespace CameraInspector