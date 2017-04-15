#include "Frame.h"

namespace CameraInspector
{

Frame::Frame(int width, int height, void* data) : cols_(width), rows_(height), data_(data)
{
}

void Frame::Construct(int width, int height, void* data)
{
	cols_ = width;
	rows_ = height;
	data_ = data;
}

int Frame::GetCols() const
{
	return cols_;
}

int Frame::GetRows() const
{
	return rows_;
}

void* Frame::GetData() const
{
	return data_;
}

} // namespace CameraInspector
