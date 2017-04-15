#include "Frame.h"

namespace CameraInspector
{

Frame::Frame(int height, int width, void* data) : cols_(height), rows_(width), data_(data)
{
}

void Frame::Construct(int height, int width, void* data)
{
	cols_ = width;
	rows_ = height;
	data_ = data;
}

int Frame::GetRows() const
{
	return rows_;
}

int Frame::GetCols() const
{
	return cols_;
}

void* Frame::GetData() const
{
	return data_;
}

} // namespace CameraInspector
