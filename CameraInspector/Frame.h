#pragma once

namespace CameraInspector
{

class Frame
{
public:
	Frame() = default;
	Frame(int width, int height, void* data);
	
	void Construct(int width, int height, void* data);

	int GetCols() const;
	int GetRows() const;
	void* GetData() const;

private:
	int cols_;		
	int rows_;		
	void* data_;	
};

} // namespace CameraInspector