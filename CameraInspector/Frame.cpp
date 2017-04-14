#include "Frame.h"

namespace CameraInspector
{

Frame::Frame(int height, int width, void* data) : cols(height), rows(width), data(data)
{
}

void Frame::Construct(int height, int width, void* data)
{
	this->cols = width;
	this->rows = height;
	this->data = data;
}

int Frame::GetRows() const
{
	return rows;
}

int Frame::GetCols() const
{
	return cols;
}

void* Frame::GetData() const
{
	return data;
}

} // namespace CameraInspector
