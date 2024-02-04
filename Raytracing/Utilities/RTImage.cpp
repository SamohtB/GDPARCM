#include "RTImage.h"


using namespace utility;

RTImage::RTImage(const int imageWidth, const int imageHeight)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;

	this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->imageHeight, this->imageWidth, CV_8UC3));
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samplesPerPixel)
{
	float scale = 1.0f / static_cast<float>(samplesPerPixel);
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	int rInt = static_cast<uchar>(256 * clamp(r, 0.0f, 0.999f));
	int gInt = static_cast<uchar>(256 * clamp(g, 0.0f, 0.999f));
	int bInt = static_cast<uchar>(256 * clamp(b, 0.0f, 0.999f));

	//std::cout << "RTImage: " << rInt << " " << gInt << " " << bInt << std::endl;

	cv::Mat imgChannels[3];
	cv::split(*this->pixels, imgChannels);

	imgChannels[0].at<uchar>(this->imageHeight - 1 - y, x) = bInt;
	imgChannels[1].at<uchar>(this->imageHeight - 1 - y, x) = gInt;
	imgChannels[2].at<uchar>(this->imageHeight - 1 - y, x) = rInt;

	cv::merge(imgChannels, 3, *this->pixels);
}

void RTImage::saveImage(cv::String& fileName) const
{
	cv::flip(*this->pixels, *this->pixels, 0);
	cv::imwrite(fileName, *this->pixels);
}


