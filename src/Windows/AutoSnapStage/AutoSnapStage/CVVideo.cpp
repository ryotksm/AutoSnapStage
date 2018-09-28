#include "stdafx.h"
#include "CVVideo.h"

#include <opencv2/highgui.hpp> // highguiのヘッダーをインクルード
#include <iostream>

#define VIDEO_SOURCE "C:\\Users\\ryo_g\\Videos\\GPSとセンサーとAI.mp4"

CVVideo::CVVideo()
{
	cap = new cv::VideoCapture();
}


CVVideo::~CVVideo()
{
}

void CVVideo::Init(HWND hWnd) {
	// オープンしていなかったらオープンする
	if (!cap->isOpened())
		//cap->open(VIDEO_SOURCE);
		cap->open(0);// open the default camera
	cv::Mat frame;
	(*cap) >> frame;
	if (!frame.empty()) {
		HDC hdc;
		hdc = GetDC(hWnd);
		mat2memHdc(hdc, frame);
		memHDC2Mat(mat2memHdc.hbmp);
	}
}

void CVVideo::Capture(HWND hWnd)
{
	// オープンしていなければ終了
	if (!cap->isOpened())
		return;

	cv::Mat frame;
	(*cap) >> frame;
	if (!frame.empty()) {
		// bitmapに変換
		HDC hdc;
		hdc = GetDC(hWnd);
		mat2memHdc(hdc, frame);
		memHDC2Mat(mat2memHdc.hbmp);
		mat2memHdc.BitBlt(hdc, 0, 0, SRCCOPY);
	}
}

void CVVideo::Quit() 
{
	cap->release();
}