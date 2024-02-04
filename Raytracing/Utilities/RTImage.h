#pragma once
#ifndef RT_IMAGE_H
#define RT_IMAGE_H

#include <vector>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "Vector3D.h"

namespace utility
{
	class RTImage
	{
	public:
		RTImage(const int imageWidth, const int imageHeight);
		void setPixel(int x, int y, float r, float g, float b, int samplesPerPixel);
		void saveImage(cv::String &fileName) const;

	private:
		std::unique_ptr<cv::Mat> pixels;
		int imageWidth;
		int imageHeight;
	};
}
#endif
